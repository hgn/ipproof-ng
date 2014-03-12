#ifndef SERVER_LISTENTER_H
#define SERVER_LISTENTER_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class ServerListenerThread : public QThread
{
	Q_OBJECT
	public:
		explicit ServerListenerThread(int ID, QObject *parent = 0);
		void run();

	signals:
		void error(QTcpSocket::SocketError socketerror);

	public slots:
		void readyRead();
		void disconnected();

	private:
		QTcpSocket *socket;
		int socketDescriptor;
};


#include <QTcpServer>

class TCPServer : public QTcpServer
{
	Q_OBJECT
	public:
		explicit TCPServer(QObject *parent = 0);
		void startServer();
	signals:

	public slots:

	protected:
		void incomingConnection(int socketDescriptor);

};

#endif // SERVER_LISTENTER_H
