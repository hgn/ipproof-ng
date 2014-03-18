#ifndef CONNECTIONSTATRECTWIDGET_H
#define CONNECTIONSTATRECTWIDGET_H

#include <QWidget>
#include <QColor>

class ConnectionStatWidget;

class ConnectionStatRectWidget : public QWidget
{
	Q_OBJECT

	public:

		ConnectionStatRectWidget(ConnectionStatWidget *, QWidget *parent = 0);
		void update_data();

	protected:

		void paintEvent(QPaintEvent *event);

	private:

		void drawRect(QPainter *qp);

		ConnectionStatWidget *m_cs_widget;

		int m_percent_received;
		QColor m_color;

        bool m_initial_resized;

};

#endif // CONNECTIONSTATRECTWIDGET_H
