#ifndef CONNECTIONSTATWIDGET_H
#define CONNECTIONSTATWIDGET_H

#include <QWidget>


class ConnectionData;
class QHBoxLayout;
class ConnectionStatRectWidget;

class ConnectionStatWidget : public QWidget
{
	Q_OBJECT

	public:

		ConnectionStatWidget(ConnectionData *, QWidget *parent = 0);
		void show(QHBoxLayout *);
		void update_data();

	private:

		ConnectionData *m_connection_data;
		ConnectionStatRectWidget *m_cs_rect_widget;

};

#endif // CONNECTIONSTATWIDGET_H
