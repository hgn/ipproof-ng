#ifndef THROUGHPUTWIDGET_H
#define THROUGHPUTWIDGET_H

#include <QWidget>

#include "mainwindow.h"

class ConnectionData;

class Throughput : public QWidget
{
  Q_OBJECT

  public:
    Throughput(MainWindow *main_window, QWidget *parent = 0);

  protected:
    void paintEvent(QPaintEvent *event);
    void drawLines(QPainter *qp);
    void drawThroughtputGraphs(QPainter *qp);
    void drawThroughputGraph(ConnectionData *, QPainter *, unsigned int now);

  private:
    MainWindow *m_main_window;

    int scale_to_y_axis(unsigned int);

};

#endif // THROUGHPUTWIDGET_H
