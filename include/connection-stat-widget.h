#ifndef CONNECTIONSTATWIDGET_H
#define CONNECTIONSTATWIDGET_H

#include <QWidget>

class QLabel;
class QGridLayout;

class ConnectionData;
class QHBoxLayout;
class ConnectionStatRectWidget;


class ConnectionStatWidget : public QWidget
{
	Q_OBJECT

	public:

		ConnectionStatWidget(ConnectionData *, QHBoxLayout *layout, QWidget *parent = 0);
		void show(QHBoxLayout *);
		void update_data();
        void update_time();
        void connection_end();
		ConnectionData *getConnectionData();

	private:

		void init_layout();
		void add_cs_rect_widget(QGridLayout *);

		ConnectionData *m_connection_data;
		ConnectionStatRectWidget *m_cs_rect_widget;
        int m_connection_state;

		QHBoxLayout *m_parent_layout;

        QLabel *m_duration;

		QLabel *m_tx_amount;
		QLabel *m_tx_bandwidth_max;
		QLabel *m_tx_bandwidth_avg;

		QLabel *m_rx_amount;
		QLabel *m_rx_bandwidth_max;
		QLabel *m_rx_bandwidth_avg;

        QLabel *m_rx_state;
        QLabel *m_tx_state;

};

#endif // CONNECTIONSTATWIDGET_H
