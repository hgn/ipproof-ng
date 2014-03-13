#include <QtGui>
#include <QMenu>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QMenuBar>
#include <QSplitter>

#include "mainwindow.h"
#include "measurement-config-dialog.h"
#include "server-listener.h"
#include "throughput-widget.h"

MainWindow::MainWindow()
{
	QWidget *widget = new QWidget;
	setCentralWidget(widget);


	QVBoxLayout *layout = new QVBoxLayout;
	layout->setMargin(5);

    add_main_content(layout);

	widget->setLayout(layout);

	createActions();
	createMenus();


	setWindowTitle(tr("Menus"));
	setMinimumSize(160, 160);
	resize(480, 320);

    startTimer(1000);
}


#include <QTextEdit>

void MainWindow::add_content_troughput_graph(QSplitter *splitter)
{
        m_throughput_widget = new Throughput(this);
        m_throughput_widget->resize(400, 200);

        splitter->addWidget(m_throughput_widget);
}


void MainWindow::add_main_content(QVBoxLayout *layout)
{
        QSplitter *splitter = new QSplitter(Qt::Vertical);
                QTextEdit *textedit1 = new QTextEdit;

        add_content_troughput_graph(splitter);

        splitter->addWidget(textedit1);

        layout->addWidget(splitter);
}


void MainWindow::timerEvent(QTimerEvent *event)
{
    //qDebug() << "Timer ID:" << event->timerId();
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

#include <QDateTime>

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


void MainWindow::add_network_connection_data(QTcpSocket *socket, unsigned int packet_len)
{
    QString id;
    ConnectionData *s;
    bool found_in_db = false;
    unsigned int timestamp = QDateTime::currentDateTime().toTime_t();

    id = get_socket_id(socket);

    QVectorIterator<ConnectionData *> i(m_connection_data);

    while (i.hasNext()) {
        s = i.next();

        if (id != s->id) {
            qDebug() << "Not identical: " << id << s->id;
            continue;
        }

        found_in_db = true;
        // found!
        s->bytes_received += packet_len;

        qDebug() << "RECEIVED DATA ALL: " << s->bytes_received;
        break;
    }

    if (found_in_db == false) {
        s = new ConnectionData();
        s->id = id;
        s->bytes_received = packet_len;
        m_connection_data.append(s);
        qDebug() << "New connection from " << id;
    }

    // update bytes_per_second vector;
    QVectorIterator< QPair< unsigned int , unsigned int > > iter(s->bytes_per_second);

    found_in_db = false;
    while (iter.hasNext()) {
        QPair< unsigned int , unsigned int > s = iter.next();

        if (s.first == timestamp) {
            s.second += packet_len;
            found_in_db = true;
            break;
        }
        qDebug() << s;
    }

    if (found_in_db == false) {
        s->bytes_per_second.append(qMakePair(timestamp, packet_len));
        qDebug() << s;
    }
}


void MainWindow::newFile()
{
    MeasurementConfigDialog *d = new MeasurementConfigDialog(this);
    d->exec();
}


void MainWindow::about()
{
    //infoLabel->setText(tr("Invoked <b>Help|About</b>"));
	QMessageBox::about(this, tr("About Menu"),
			tr("The <b>Menu</b> example shows how to create "
				"menu-bar menus and context menus."));
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
