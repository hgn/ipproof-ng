#include "throughput-widget.h"
#include <QPainter>


Throughput::Throughput(MainWindow *main_window, QWidget *parent)
    : QWidget(parent)
{
    m_main_window = main_window;
}


void Throughput::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter qp(this);
    drawLines(&qp);
    drawThroughtputGraphs(&qp);
}

#include <QDebug>

#define OUTER_PADDING 20
#define GRID_SPACE 40

void Throughput::drawThroughtputGraphs(QPainter *qp)
{
    QVector<ConnectionData *> connection_data;

    connection_data = m_main_window->get_connection_data();

}

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
    qp->drawRect(OUTER_PADDING, OUTER_PADDING, this->width() - OUTER_PADDING * 2,
                 this->height() - OUTER_PADDING * 2);


    QPen pen(Qt::black, 1, Qt::DotLine);
    qp->setPen(pen);
    for (i = OUTER_PADDING * 2; i < this->height() - OUTER_PADDING * 2; i += GRID_SPACE) {
        qp->drawLine(OUTER_PADDING, i,  this->width() - OUTER_PADDING, i);
    }
}
