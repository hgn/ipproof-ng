#include "throughput-widget.h"
#include <QPainter>
#include <QDateTime>
#include <QDebug>

#include "connection-stat-rect-widget.h"
#include "mainwindow.h"



ConnectionStatRectWidget::ConnectionStatRectWidget(ConnectionStatWidget *csw, QWidget *parent)
    : QWidget(parent)
{
	m_cs_widget = csw;
}


void ConnectionStatRectWidget::paintEvent(QPaintEvent *e)
{
	Q_UNUSED(e);
	QPainter qp(this);
	drawRect(&qp);
}



void ConnectionStatRectWidget::drawRect(QPainter *qp)
{
	int i;

	this->width();
	this->width();

	//qp->setPen(Qt::darkGray);

	QRectF rect(0, 0, this->width() - 10, 200 - 10);

	qp->setBrush(QBrush(QColor(100, 100, 100, 255)));
	qp->setRenderHint(QPainter::Antialiasing,true);
	qp->drawRoundedRect(rect.translated(0.5,0.5), 4.0, 4.0 );

	//qp->drawRect(0, 0, this->width(), 200);

	//qp->setBrush(QBrush(QColor(200, 200, 200, 255)));
	//qp->drawRect(0 + 2, 0 + 2, this->width() - 4, 200 - 4);

	//qp->setPen(Qt::darkGray);
	//qp->drawRect(0 + 5, 0 + 5, this->width() - 10, 200 - 10);


	resize(this->width(), 200);
}


void ConnectionStatRectWidget::update_data()
{
}

