#include <QtGui>
#include <QMenu>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QMenuBar>
#include <QSplitter>
#include <QDateTime>
#include <QTextEdit>
#include <QFrame>
#include <QLabel>
#include <QGridLayout>


#include "mainwindow.h"
#include "measurement-config-dialog.h"
#include "server-listener.h"
#include "throughput-widget.h"


ColorPicker* ColorPicker::m_pInstance = NULL;

ColorPicker* ColorPicker::Instance()
{
	if (!m_pInstance)
		m_pInstance = new ColorPicker;
	return m_pInstance;
}

ColorPicker::ColorPicker()
{
	m_index = 0;

	m_data[0] = QColor(Qt::red);
	m_data[1] = QColor(Qt::blue);
	m_data[2] = QColor(Qt::green);
	m_data[3] = QColor(Qt::cyan);
	m_data[4] = QColor(Qt::yellow);
	m_data[5] = QColor(Qt::darkBlue);
	m_data[6] = QColor(Qt::darkRed);
	m_data[7] = QColor(Qt::darkCyan);
}


QColor ColorPicker::next()
{
	QColor ret = m_data[m_index];
	m_index = (++m_index) % sizeof(m_data);
	return ret;
}


MainWindow::MainWindow()
{
	QWidget *widget = new QWidget;
	setCentralWidget(widget);
	QObject::connect(this, SIGNAL(new_data(QTcpSocket *, unsigned int)), this, SLOT(add_network_connection_data_slot(QTcpSocket *, unsigned int)));
    QObject::connect(this, SIGNAL(connection_end_signal(QString)), this, SLOT(connection_end_slot(QString)));


	QVBoxLayout *layout = new QVBoxLayout;
	layout->setMargin(5);

	add_main_content(layout);

	widget->setLayout(layout);

	createActions();
	createMenus();

	setWindowTitle("IPProof Next Generation - Server");
	setMinimumSize(460, 460);
	showMaximized();

    m_bytes_per_second_max = 0;

    startTimer(1000);
}


void MainWindow::newConnection(int socket)
{
	(void)socket;
}

void MainWindow::add_content_troughput_graph(QSplitter *splitter)
{
	m_throughput_widget = new Throughput(this);
	m_throughput_widget->resize(400, 200);

	splitter->addWidget(m_throughput_widget);
}

void MainWindow::add_status_widget(void)
{
}

void MainWindow::add_main_content(QVBoxLayout *layout)
{
	QSplitter *splitter = new QSplitter(Qt::Vertical);
	QWidget *container = new QWidget;
	QVBoxLayout *box =  new QVBoxLayout;
	m_lower_status_layout = new QHBoxLayout;

	add_content_troughput_graph(splitter);

	QLabel *label = new QLabel();
	QPixmap pixmap(":/image-ipproof-foo.png");
	label->setPixmap(pixmap);
	label->setMask(pixmap.mask());
	label->setStyleSheet("QLabel { color: #555555; font-size: 32px; font-weight:100; }");
	box->addWidget(label);


	box->addLayout(m_lower_status_layout);

	container->setLayout(box);
	splitter->addWidget(container);
	layout->addWidget(splitter);

	box->addStretch(1);

	add_status_widget();
}


void MainWindow::timerEvent(QTimerEvent *event)
{
    ConnectionData *s;
	(void)event;

    m_connection_data_mutex.lock();
    QVectorIterator<ConnectionData *> i(m_connection_data);

    while (i.hasNext()) {
        s = i.next();
        s->connection_stat_widget->update_time();

    }
    m_connection_data_mutex.unlock();

    // we repaint the throughput widget as well
    m_throughput_widget->repaint();
}


void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu menu(this);
	menu.exec(event->globalPos());
}


void MainWindow::set_expected_bytes(unsigned int bytes)
{
	m_expected_bytes = bytes;
}


void MainWindow::close_listening_sockets()
{
	QVectorIterator<TCPServer *> i(m_tcp_servers);

	while (i.hasNext()) {
		TCPServer *s = i.next();
		s->close();
		delete s;
	}

	m_tcp_servers.clear();
}


void MainWindow::set_listening_ports(int ports[], int ports_no)
{
	int i;

	close_listening_sockets();

	for (i = 0; i < ports_no; i++) {
		qWarning() << "Listening on port: " << ports[i];
		TCPServer *server = new TCPServer();
		server->register_main_window(this);
		m_tcp_servers.append(server);
		server->startServer(ports[i]);
	}
}


QString MainWindow::get_socket_id(QTcpSocket *s)
{

	return  QString("%1:%2:%3:%4")
		.arg(s->peerAddress().toString())
		.arg(s->peerPort())
		.arg(s->localAddress().toString())
		.arg(s->localPort());
}


QVector<ConnectionData *> MainWindow::get_connection_data()
{
	return m_connection_data;
}


void MainWindow::register_new_connectio_stat(ConnectionData *conn_data)
{
	conn_data->connection_stat_widget =
		new ConnectionStatWidget(conn_data, m_lower_status_layout);
}

unsigned int MainWindow::get_max_bandwidth()
{
    return m_bytes_per_second_max;
}


void MainWindow::connection_end(QString id)
{
    qDebug() << "CONNECTION END";
    emit connection_end_signal(id);
}


void MainWindow::connection_end_slot(QString id)
{
    ConnectionData *s;

    m_connection_data_mutex.lock();
    QVectorIterator<ConnectionData *> i(m_connection_data);

    while (i.hasNext()) {
        s = i.next();
        if (id != s->id)
            continue;

        s->connection_stat_widget->connection_end();
        break;
    }
    m_connection_data_mutex.unlock();
}


void MainWindow::add_network_connection_data(QTcpSocket *socket, unsigned int packet_len)
{
	emit new_data(socket, packet_len);
}


void MainWindow::add_network_connection_data_slot(QTcpSocket *socket, unsigned int packet_len)
{
	QString id;
	ConnectionData *s;
	bool found_in_db = false;
	unsigned int timestamp = QDateTime::currentDateTime().toTime_t();

	id = get_socket_id(socket);

	m_connection_data_mutex.lock();
	QVectorIterator<ConnectionData *> i(m_connection_data);

	while (i.hasNext()) {
		s = i.next();

		if (id != s->id) {
			continue;
		}

		found_in_db = true;
		s->bytes_received += packet_len;
		s->connection_stat_widget->update_data();
		break;
	}
	m_connection_data_mutex.unlock();

	if (found_in_db == false) {
		s = new ConnectionData();
        s->start_time.start();

		s->id = id;
        s->sip = QString("%1").arg(socket->localAddress().toString());
        s->dip = QString("%1").arg(socket->peerAddress().toString());
        s->sport = QString("%1").arg(socket->localPort());
        s->dport = QString("%1").arg(socket->peerPort());

		s->bytes_received = packet_len;
		s->bytes_expected = 30000;
		s->color = ColorPicker::Instance()->next();
		register_new_connectio_stat(s);

		m_connection_data_mutex.lock();
		m_connection_data.append(s);
		m_connection_data_mutex.unlock();
		qDebug() << "New connection from " << id;
	}

	// update bytes_per_second vector;
	QVectorIterator< QPair< unsigned int , unsigned int > > iter(s->bytes_per_second);

	found_in_db = false;
	while (iter.hasNext()) {
		QPair< unsigned int , unsigned int > s = iter.next();

		if (s.first == timestamp) {
			s.second += packet_len;
            if (s.second > m_bytes_per_second_max) {
                // update the global max byte/s
                m_bytes_per_second_max = s.second;
            }
			found_in_db = true;
			break;
		}
	}

	if (found_in_db == false) {
		s->bytes_per_second.append(qMakePair(timestamp, packet_len));
	}
}


void MainWindow::newFile()
{
	MeasurementConfigDialog *d = new MeasurementConfigDialog(this);
	d->exec();
}


void MainWindow::show_dialog()
{
    newFile();
}


void MainWindow::about()
{
	QMessageBox::about(this, tr("About Menu"),
			"<b>IPProof</b> is Free Software and licenced under "
			"GPLv3 (or higher).<br ><br >"
			"Contact: Hagen Paul Pfeifer &lt;hagen@jauu.net&gt;<br ><br >"
			"URL: http://research.protocollabs.com/ipproof/");
}


void MainWindow::createActions()
{
	newAct = new QAction(tr("&New"), this);
	newAct->setShortcuts(QKeySequence::New);
	newAct->setStatusTip(tr("Create a new file"));
	connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));


	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcuts(QKeySequence::Quit);
	exitAct->setStatusTip(tr("Exit the application"));
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));


	aboutAct = new QAction(tr("&About"), this);
	aboutAct->setStatusTip(tr("Show the application's About box"));
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);


	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAct);

}
