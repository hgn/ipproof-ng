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



#define CONNECTION_STATE_ACTIVE 1
#define CONNECTION_STATE_END 2


ConnectionStatWidget::ConnectionStatWidget(ConnectionData *cn,
		QHBoxLayout *layout, QWidget *parent)
    : QWidget(parent)
{
	m_connection_data = cn;
	m_parent_layout = layout;
    m_connection_state = CONNECTION_STATE_ACTIVE;

	init_layout();
}


void ConnectionStatWidget::connection_end()
{
    m_connection_state = CONNECTION_STATE_END;
}



/* called when new data is available */
void ConnectionStatWidget::update_data()
{
    if (m_connection_state == CONNECTION_STATE_END) {
        // no update required anymore
        return;
    }

	m_cs_rect_widget->update_data();

    int difference = m_connection_data->start_time.elapsed();

    m_rx_amount->setText(QString("RX Data: %1 byte")
                         .arg(m_connection_data->bytes_received));

    if (difference > 0) {
        float diff = (float)difference / 1000.0;
        int rx = (int)((float)(m_connection_data->bytes_received * 8.0) / diff);
        m_rx_bandwidth_avg->setText(QString("RX Goodput AVG: %1 bit/s")
                                   .arg(rx));
    }
}


void ConnectionStatWidget::update_time()
{
    if (m_connection_state == CONNECTION_STATE_END) {
        // no update required anymore
        m_rx_state->setText(QString("RX State: closed"));
        m_tx_state->setText(QString("TX State: closed"));
        return;
    }

    int difference = m_connection_data->start_time.elapsed();

    int secs  = difference / 1000;
    int msec  = difference - (secs * 1000);
    int mins  = (secs / 60) % 60;
    int hours = (secs / 3600);
    secs = secs % 60;

    m_duration->setText(QString("Connection Time: %1:%2:%3.%4")
        .arg(hours, 2, 10, QLatin1Char('0'))
        .arg(mins, 2, 10, QLatin1Char('0'))
        .arg(secs, 2, 10, QLatin1Char('0'))
        .arg(msec, 3, 10, QLatin1Char('0')));

    m_rx_amount->setText(QString("RX Data: %1 byte")
                         .arg(m_connection_data->bytes_received));

    if (difference > 0) {
        float diff = (float)difference / 1000.0;
        int rx = (int)((float)(m_connection_data->bytes_received * 8) / diff);
        m_rx_bandwidth_avg->setText(QString("RX Goodput AVG: %1 bit/s")
                                   .arg(rx));
    }
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

    m_duration = new QLabel("Connection Time: 00:00:00.000", 0);
    m_duration->setStyleSheet("QLabel { color: #555555; font-size: 22px; font-weight:100; }");
    layout->addWidget(m_duration, 0, 0, 1, 0);

    QLabel *l2 = new QLabel();
    l2->setText(QString("%1:%2 - %3:%4")
                .arg(m_connection_data->sip)
                .arg(m_connection_data->sport)
                .arg(m_connection_data->dip)
                .arg(m_connection_data->dport));
    l2->setStyleSheet("QLabel { color: #777777; font-size: 14px; font-weight:100; }");
    layout->addWidget(l2, 1, 0, 1, 0);

    m_rx_amount = new QLabel("RX Data:  0 byte", 0);
    m_rx_amount->setStyleSheet("QLabel { color: #555555; font-size: 19px; font-weight:100; }");
    layout->addWidget(m_rx_amount, 2, 0);

    m_tx_amount = new QLabel("TX Data:  0 byte", 0);
    m_tx_amount->setStyleSheet("QLabel { color: #555555; font-size: 19px; font-weight:100; }");
    layout->addWidget(m_tx_amount, 2, 1);

    m_rx_bandwidth_avg = new QLabel("RX Goodput AVG: - byte/s", 0);
    m_rx_bandwidth_avg->setStyleSheet("QLabel { color: #555555; font-size: 19px; font-weight:100; }");
    layout->addWidget(m_rx_bandwidth_avg, 3, 0);

    m_tx_bandwidth_avg = new QLabel("TX Goodput AVG: - byte/s", 0);
    m_tx_bandwidth_avg->setStyleSheet("QLabel { color: #555555; font-size: 19px; font-weight:100; }");
    layout->addWidget(m_tx_bandwidth_avg, 3, 1);

    m_rx_state = new QLabel("RX State: open", 0);
    m_rx_state->setStyleSheet("QLabel { color: #555555; font-size: 17px; font-weight:100; }");
    layout->addWidget(m_rx_state, 4, 0);

    m_tx_state = new QLabel("TX State: open", 0);
    m_tx_state->setStyleSheet("QLabel { color: #555555; font-size: 17px; font-weight:100; }");
    layout->addWidget(m_tx_state, 4, 1);

	add_cs_rect_widget(layout);

	m_parent_layout->addLayout(layout);
}
