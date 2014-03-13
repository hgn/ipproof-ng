#ifndef SERVER_LISTENTER_H
#define SERVER_LISTENTER_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>


class MainWindow;

class ServerListenerThread : public QThread
{
	Q_OBJECT
	public:
		explicit ServerListenerThread(int ID, QObject *parent = 0);
		void run();
        void set_main_window(MainWindow *);

	signals:
		void error(QTcpSocket::SocketError socketerror);

	public slots:
		void readyRead();
		void disconnected();

	private:
		QTcpSocket *socket;
		int socketDescriptor;
        MainWindow *m_main_window;
};

#include <QTcpServer>

class MainWindow;

class TCPServer : public QTcpServer
{
	Q_OBJECT

	public:
        explicit TCPServer(QObject *parent = 0);

        void startServer(int port);
        void close();

        void register_main_window(MainWindow *);

	signals:

	public slots:

	protected:
		void incomingConnection(int socketDescriptor);

    private:
        int m_port;
        MainWindow *m_main_window;
};

#endif // SERVER_LISTENTER_H
