#include "server-listener.h"
#include "mainwindow.h"


ServerListenerThread::ServerListenerThread(int ID, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;
}


void ServerListenerThread::set_main_window(MainWindow *main_window)
{
    m_main_window = main_window;
}


void ServerListenerThread::run()
{
    qDebug() << " Thread started";

    socket = new QTcpSocket();

    if(!socket->setSocketDescriptor(this->socketDescriptor)) {

        emit error(socket->error());
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));


    qDebug() << socketDescriptor << " Client connected";

    exec();
}

void ServerListenerThread::readyRead()
{
    // get the information
    QByteArray Data = socket->readAll();

    // will write on server side window
    //qDebug() << socketDescriptor << " Data in: " << Data.length();

    m_main_window->add_network_connection_data(socket, Data.length());

    //socket->write(Data);
}

void ServerListenerThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";


    socket->deleteLater();
    exit(0);
}



TCPServer::TCPServer(QObject *parent) :
	QTcpServer(parent)
{
}

void TCPServer::register_main_window(MainWindow *window)
{
    m_main_window = window;
}


void TCPServer::startServer(int port)
{
	m_port = port;

	qDebug() << "Start TCP Server";

	if(!this->listen(QHostAddress::Any, port)) {
		qDebug() << "Could not start server";
	} else {
		qDebug() << "Listening to port: " << port;
	}

	qWarning() << "listen now";
}


void TCPServer::close()
{
    QTcpServer::close();
}


void TCPServer::incomingConnection(int socketDescriptor)
{
	qDebug() << socketDescriptor << " Connecting...";

	ServerListenerThread *thread = new ServerListenerThread(socketDescriptor, this);
	thread->set_main_window(m_main_window);

	m_main_window->newConnection(socketDescriptor);

	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

	thread->start();
}
