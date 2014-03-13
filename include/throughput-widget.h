#ifndef THROUGHPUTWIDGET_H
#define THROUGHPUTWIDGET_H

#include <QWidget>

#include "mainwindow.h"

class Throughput : public QWidget
{
  Q_OBJECT

  public:
    Throughput(MainWindow *main_window, QWidget *parent = 0);

  protected:
    void paintEvent(QPaintEvent *event);
    void drawLines(QPainter *qp);
    void drawThroughtputGraphs(QPainter *qp);

  private:
    MainWindow *m_main_window;

};

#endif // THROUGHPUTWIDGET_H
