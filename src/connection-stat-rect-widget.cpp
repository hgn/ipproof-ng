#include "throughput-widget.h"
#include <QPainter>
#include <QDateTime>
#include <QDebug>
#include <QColor>

#include "connection-stat-rect-widget.h"
#include "mainwindow.h"



ConnectionStatRectWidget::ConnectionStatRectWidget(ConnectionStatWidget *csw, QWidget *parent)
    : QWidget(parent)
{
	m_cs_widget = csw;
	m_percent_received = 0;

	m_color = QColor(csw->getConnectionData()->color);
}


void ConnectionStatRectWidget::paintEvent(QPaintEvent *e)
{
	Q_UNUSED(e);
	QPainter qp(this);
	drawRect(&qp);
}

#define H 200

void ConnectionStatRectWidget::drawRect(QPainter *qp)
{
	int i;

	// draw background
	QRectF rect(0, 0, this->width() - 10, H);
	qp->setBrush(QBrush(QColor(100, 100, 100, 255)));
	qp->setRenderHint(QPainter::Antialiasing,true);
	qp->drawRoundedRect(rect.translated(0.5,0.5), 5.0, 5.0 );

	// draw filled rect
	if (m_percent_received > 0) {
		int height = (int)(H * ((float)m_percent_received / 100.0));
		int dist = H - height;
		QRectF frect(0, dist, this->width() - 10, height);
		qp->setBrush(QBrush(m_color));
		qp->drawRoundedRect(frect.translated(0.5,0.5), 5.0, 5.0 );
	}

	resize(this->width(), H + 10);
}


void ConnectionStatRectWidget::update_data()
{
	// get data
	ConnectionData *conn_data = m_cs_widget->getConnectionData();

	qDebug() << "Bytes Received: " << conn_data->bytes_received;
	qDebug() << "Bytes Expected: " << conn_data->bytes_expected;

	m_percent_received = conn_data->bytes_received / (conn_data->bytes_expected / 100);
	m_percent_received = qMin(m_percent_received, 100);
	m_percent_received = qMax(m_percent_received, 0);

	qDebug() << "Percent: " << m_percent_received;

	repaint();
}

