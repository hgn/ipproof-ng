#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QVector>
#include <QSplitter>
#include <QColor>


#include "server-listener.h"
#include "throughput-widget.h"

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
   //ColorPicker& operator=(ColorPicker const&){};
   static ColorPicker* m_pInstance;
   int m_index;
   QColor m_data[8];
};


struct ConnectionData {
    QString id;
    unsigned int bytes_received;
    unsigned int data_start;
    QColor color;
    QVector< QPair< unsigned int , unsigned int > > bytes_per_second;
};

class Throughput;

 class MainWindow : public QMainWindow
 {
     Q_OBJECT

 public:
     MainWindow();

     void show_dialog();
     void set_expected_bytes(unsigned int);
     void set_listening_ports(int ports[], int ports_no);

     void add_network_connection_data(QTcpSocket *socket, unsigned int packet_len);

     QVector<ConnectionData *> get_connection_data();

 protected:
     void contextMenuEvent(QContextMenuEvent *event);
     void timerEvent(QTimerEvent *event);

 private slots:
     void newFile();
     void about();


 private:

     void add_content_troughput_graph(QSplitter *splitter);
     void add_main_content(QVBoxLayout *layout);

     QString get_socket_id(QTcpSocket *);

     Throughput *m_throughput_widget;

     void createActions();
     void createMenus();

     void close_listening_sockets();

     QVector<TCPServer *> m_tcp_servers;
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
