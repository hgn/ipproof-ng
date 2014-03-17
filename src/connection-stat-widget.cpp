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

	QLabel *l1 = new QLabel("Duration", 0);
	l1->setStyleSheet("QLabel { color: #555555; font-size: 22px; font-weight:100; }");
	layout->addWidget(l1, 0, 0, 1, 0);

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
