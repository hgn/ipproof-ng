#include "server-listener.h"

ServerListenerThread::ServerListenerThread(int ID, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;
}

void ServerListenerThread::run()
{
    // thread starts here
    qDebug() << " Thread started";

    socket = new QTcpSocket();

    // set the ID
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        // something's wrong, we just emit a signal
        emit error(socket->error());
        return;
    }

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    // We'll have multiple clients, we want to know which is which
    qDebug() << socketDescriptor << " Client connected";

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies

    exec();
}

void ServerListenerThread::readyRead()
{
    // get the information
    QByteArray Data = socket->readAll();

    // will write on server side window
    qDebug() << socketDescriptor << " Data in: " << Data;

    socket->write(Data);
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

void TCPServer::startServer()
{
	int port = 1234;

	if(!this->listen(QHostAddress::Any, port))
	{
		qDebug() << "Could not start server";
	}
	else
	{
		qDebug() << "Listening to port " << port << "...";
	}
}

// This function is called by QTcpServer when a new connection is available. 
void TCPServer::incomingConnection(int socketDescriptor)
{
	// We have a new connection
	qDebug() << socketDescriptor << " Connecting...";

	// Every new connection will be run in a newly created thread
	ServerListenerThread *thread = new ServerListenerThread(socketDescriptor, this);

	// connect signal/slot
	// once a thread is not needed, it will be beleted later
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

	thread->start();
}
