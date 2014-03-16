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
}


void ConnectionStatRectWidget::update_data()
{
}

