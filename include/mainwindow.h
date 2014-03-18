#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QVector>
#include <QSplitter>
#include <QColor>
#include <QMutex>
#include <QTime>

#include "server-listener.h"
#include "throughput-widget.h"
#include "connection-stat-widget.h"


class QAction;
class QActionGroup;
class QLabel;
class QMenu;



class ColorPicker {
	public:

		static ColorPicker* Instance();
		QColor next();

	private:

		ColorPicker();
		ColorPicker(ColorPicker const&){};
		static ColorPicker* m_pInstance;
		int m_index;
		QColor m_data[8];
};


class Throughput;

struct ConnectionData {
	QString id;
    QString sip;
    QString dip;
    QString sport;
    QString dport;
	unsigned int bytes_received;
	unsigned int bytes_expected;
	unsigned int data_start;
	QColor color;
	QVector< QPair< unsigned int , unsigned int > > bytes_per_second;
	ConnectionStatWidget *connection_stat_widget;
    QTime start_time;
};

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		MainWindow();

		void show_dialog();
		void set_expected_bytes(unsigned int);
		void set_listening_ports(int ports[], int ports_no);

		QVector<ConnectionData *> get_connection_data();
		void newConnection(int);
		void add_network_connection_data(QTcpSocket *socket, unsigned int packet_len);
        void connection_end(QString id);
		QMutex m_connection_data_mutex;

        unsigned int get_max_bandwidth();

	signals:
		void new_data(QTcpSocket *socket, unsigned int packet_len);
        void connection_end_signal(QString id);

	public slots:

		void add_network_connection_data_slot(QTcpSocket *socket, unsigned int packet_len);
        void connection_end_slot(QString id);

	protected:

		void contextMenuEvent(QContextMenuEvent *event);
		void timerEvent(QTimerEvent *event);



	private slots:

		void newFile();
		void about();

	private:

		void register_new_connectio_stat(ConnectionData *);
		void add_content_troughput_graph(QSplitter *splitter);
		void add_main_content(QVBoxLayout *layout);
		void add_status_widget();

		QString get_socket_id(QTcpSocket *);

		QHBoxLayout *m_lower_status_layout;

		Throughput *m_throughput_widget;

		void createActions();
		void createMenus();

		void close_listening_sockets();

		QVector<TCPServer *> m_tcp_servers;
        unsigned int m_bytes_per_second_max;
		QVector<ConnectionData *> m_connection_data;

		unsigned int m_expected_bytes;

		QMenu *fileMenu;
		QMenu *helpMenu;

		QActionGroup *alignmentGroup;
		QAction *newAct;
		QAction *exitAct;
		QAction *aboutAct;
		QAction *aboutQtAct;
		QLabel *infoLabel;
};

 #endif
