#ifndef CONNECTIONSTATWIDGET_H
#define CONNECTIONSTATWIDGET_H

#include <QWidget>


class ConnectionData;
class QHBoxLayout;

class ConnectionStatWidget : public QWidget
{
	Q_OBJECT

	public:

		ConnectionStatWidget(QWidget *parent = 0);
		void show(QHBoxLayout *);
		void register_connection_data(ConnectionData *);
		void update_data();

	private:

		ConnectionData *m_connection_data;

};

#endif // CONNECTIONSTATWIDGET_H
