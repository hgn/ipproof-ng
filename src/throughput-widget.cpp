#include "throughput-widget.h"
#include <QPainter>


Throughput::Throughput(QWidget *parent)
    : QWidget(parent)
{

}


void Throughput::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter qp(this);
    drawLines(&qp);
}

#include <QDebug>


void Throughput::drawLines(QPainter *qp)
{
    int i;

    qWarning() << this->height();
    qWarning() << this->width();

    // background
    qp->setBrush(QBrush("#bbbbbb"));
    qp->drawRect(0, 0, this->width(), this->height());

    // padding from all sides: 40px
    qp->setBrush(QBrush("#999999"));
    qp->drawRect(20, 20, this->width() - 40, this->height() - 40);



    QPen pen(Qt::black, 1, Qt::DotLine);
    qp->setPen(pen);
    for (i = 40; i < this->height() - 40; i += 40) {
        qp->drawLine(20, i,  this->width() - 40, i);
    }

}
