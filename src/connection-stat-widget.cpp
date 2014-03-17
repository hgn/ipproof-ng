#include "throughput-widget.h"
#include <QPainter>
#include <QDateTime>
#include <QDebug>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>

#include "connection-stat-widget.h"
#include "connection-stat-rect-widget.h"
#include "mainwindow.h"


ConnectionStatWidget::ConnectionStatWidget(ConnectionData *cn,
		QHBoxLayout *layout, QWidget *parent)
    : QWidget(parent)
{
	m_connection_data = cn;
	m_parent_layout = layout;

	init_layout();
}


/* called when new data is available */
void ConnectionStatWidget::update_data()
{
	m_cs_rect_widget->update_data();

     int difference = m_connection_data->start_time.elapsed();

    m_rx_amount->setText(QString("Amount: - %1 byte")
                         .arg(m_connection_data->bytes_received));

    if (difference > 0) {
        float diff = (float)difference / 1000.0;
        int rx = (int)((float)m_connection_data->bytes_received / diff);
        m_rx_bandwidth_avg->setText(QString("Bandwidth AVG: - %1 byte/s")
                                   .arg(rx));
    }
}


void ConnectionStatWidget::update_time()
{

    int difference = m_connection_data->start_time.elapsed();

    int secs  = difference / 1000;
    int msec  = difference - (secs * 1000);
    int mins  = (secs / 60) % 60;
    int hours = (secs / 3600);
    secs = secs % 60;

    m_duration->setText(QString("Duration %1:%2:%3.%4")
        .arg(hours, 2, 10, QLatin1Char('0'))
        .arg(mins, 2, 10, QLatin1Char('0'))
        .arg(secs, 2, 10, QLatin1Char('0'))
        .arg(msec, 3, 10, QLatin1Char('0')));
}


ConnectionData *ConnectionStatWidget::getConnectionData()
{
	return m_connection_data;
}


void ConnectionStatWidget::add_cs_rect_widget(QGridLayout *l)
{
	m_cs_rect_widget = new ConnectionStatRectWidget(this);
	l->addWidget(m_cs_rect_widget, 5, 0);

	QLabel *l1 = new QLabel("", 0);
	l->addWidget(l1, 5, 1);
}


void ConnectionStatWidget::init_layout()
{
	QGridLayout *layout = new QGridLayout;

    m_duration = new QLabel("Duration: 00:00:00.000", 0);
    m_duration->setStyleSheet("QLabel { color: #555555; font-size: 22px; font-weight:100; }");
    layout->addWidget(m_duration, 0, 0, 1, 0);

	QLabel *l2 = new QLabel("Receive", 0);
	l2->setStyleSheet("QLabel { color: #555555; font-size: 17px; font-weight:100; }");
	layout->addWidget(l2, 1, 0);

	QLabel *l3 = new QLabel("Transmit", 0);
	l3->setStyleSheet("QLabel { color: #555555; font-size: 17px; font-weight:100; }");
	layout->addWidget(l3, 1, 1);

	// FIXME
	int i = m_connection_data->bytes_received;

	m_tx_amount = new QLabel("Amount: - byte", 0);
	m_tx_amount->setStyleSheet("QLabel { color: #555555; font-size: 17px; font-weight:100; }");
	layout->addWidget(m_tx_amount, 2, 0);

	m_rx_amount = new QLabel("Amount: - byte", 0);
	m_rx_amount->setStyleSheet("QLabel { color: #555555; font-size: 17px; font-weight:100; }");
	layout->addWidget(m_rx_amount, 2, 1);

	m_tx_bandwidth_max = new QLabel("Bandwidth MAX: - byte/s", 0);
	m_tx_bandwidth_max->setStyleSheet("QLabel { color: #555555; font-size: 17px; font-weight:100; }");
	layout->addWidget(m_tx_bandwidth_max, 3, 0);

	m_tx_bandwidth_avg = new QLabel("Bandwidth AVG: - byte/s", 0);
	m_tx_bandwidth_avg->setStyleSheet("QLabel { color: #555555; font-size: 17px; font-weight:100; }");
	layout->addWidget(m_tx_bandwidth_avg, 3, 1);

	m_rx_bandwidth_max = new QLabel("Bandwidth MAX: - byte/s", 0);
	m_rx_bandwidth_max->setStyleSheet("QLabel { color: #555555; font-size: 17px; font-weight:100; }");
	layout->addWidget(m_rx_bandwidth_max, 4, 0);

	m_rx_bandwidth_avg = new QLabel("Bandwidth AVG: - byte/s", 0);
	m_rx_bandwidth_avg->setStyleSheet("QLabel { color: #555555; font-size: 17px; font-weight:100; }");
	layout->addWidget(m_rx_bandwidth_avg, 4, 1);

	add_cs_rect_widget(layout);

	m_parent_layout->addLayout(layout);
}
