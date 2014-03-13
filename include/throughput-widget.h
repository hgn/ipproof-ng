#ifndef THROUGHPUTWIDGET_H
#define THROUGHPUTWIDGET_H

#include <QWidget>

class Throughput : public QWidget
{
  Q_OBJECT

  public:
    Throughput(QWidget *parent = 0);

  protected:
    void paintEvent(QPaintEvent *event);
    void drawLines(QPainter *qp);

};

#endif // THROUGHPUTWIDGET_H
