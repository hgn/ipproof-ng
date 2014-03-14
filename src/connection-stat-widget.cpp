#include "throughput-widget.h"
#include <QPainter>
#include <QDateTime>
#include <QDebug>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>

#include "connection-stat-widget.h"
#include "mainwindow.h"


ConnectionStatWidget::ConnectionStatWidget(QWidget *parent)
    : QWidget(parent)
{
}


void ConnectionStatWidget::register_connection_data(ConnectionData *data)
{
	m_connection_data = data;
}


/* called when new data is available */
void ConnectionStatWidget::update_data()
{
}


void ConnectionStatWidget::show(QHBoxLayout *parent)
{
	QGridLayout *layout = new QGridLayout;

	QLabel *l1 = new QLabel("Duration", 0);
	l1->setStyleSheet("QLabel { color: #555555; font-size: 22px; font-weight:100; }");
	//layout->addWidget(l1);
	layout->addWidget(l1, 0, 0);

	QLabel *l2 = new QLabel("Receive", 0);
	l2->setStyleSheet("QLabel { color: #555555; font-size: 17px; font-weight:100; }");
	//layout->addWidget(l2);
	layout->addWidget(l2, 1, 0);

	QLabel *l3 = new QLabel("Transmit", 0);
	l3->setStyleSheet("QLabel { color: #555555; font-size: 17px; font-weight:100; }");
	//layout->addWidget(l2);
	layout->addWidget(l3, 1, 1);

	int i = m_connection_data->bytes_received;

	QLabel *l4 = new QLabel("Amount: - byte", 0);
	l4->setStyleSheet("QLabel { color: #555555; font-size: 17px; font-weight:100; }");
	//layout->addWidget(l2);
	layout->addWidget(l4, 2, 0);

	QLabel *l5 = new QLabel("Amount: - byte", 0);
	l5->setStyleSheet("QLabel { color: #555555; font-size: 17px; font-weight:100; }");
	//layout->addWidget(l2);
	layout->addWidget(l5, 2, 1);

	QLabel *l6 = new QLabel("Bandwidth MAX: - byte/s", 0);
	l6->setStyleSheet("QLabel { color: #555555; font-size: 17px; font-weight:100; }");
	//layout->addWidget(l2);
	layout->addWidget(l6, 3, 0);

	QLabel *l7 = new QLabel("Bandwidth AVG: - byte/s", 0);
	l7->setStyleSheet("QLabel { color: #555555; font-size: 17px; font-weight:100; }");
	//layout->addWidget(l2);
	layout->addWidget(l7, 3, 1);

	QLabel *l8 = new QLabel("Bandwidth MAX: - byte/s", 0);
	l8->setStyleSheet("QLabel { color: #555555; font-size: 17px; font-weight:100; }");
	//layout->addWidget(l2);
	layout->addWidget(l8, 4, 0);

	QLabel *l9 = new QLabel("Bandwidth AVG: - byte/s", 0);
	l9->setStyleSheet("QLabel { color: #555555; font-size: 17px; font-weight:100; }");
	//layout->addWidget(l2);
	layout->addWidget(l9, 4, 1);

	parent->addLayout(layout);
}
