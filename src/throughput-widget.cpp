#include "throughput-widget.h"
#include <QPainter>
#include <QDateTime>
#include <QDebug>



Throughput::Throughput(MainWindow *main_window, QWidget *parent)
    : QWidget(parent)
{
	m_main_window = main_window;
}


void Throughput::paintEvent(QPaintEvent *e)
{
	Q_UNUSED(e);
	QPainter qp(this);
	drawLines(&qp);
	drawThroughtputGraphs(&qp);
}

#define OUTER_PADDING 20
#define GRID_SPACE 40

// in seconds
#define TIME_TO_VISUALIZE 30


static int draw_width;
static int draw_start_right;


int Throughput::scale_to_y_axis(unsigned int bytes_per_second)
{
	int avail_height = this->height() - OUTER_PADDING * 2;
	unsigned int max_val = m_main_window->get_max_bandwidth();

	float percent = ((float)bytes_per_second / ((float)max_val));
	float height = avail_height * percent;

	qDebug() << "new height: " << bytes_per_second;

	return (int)(this->height() - height + OUTER_PADDING);
}


void Throughput::drawThroughputGraph(ConnectionData *cn, QPainter *qp, unsigned int now)
{
	int x_prev = draw_start_right;
	int x_pos = draw_start_right;
	int gap_distance;
	int y_prev = scale_to_y_axis(0);;
	int y_pos;
	unsigned int i;
	QVectorIterator< QPair< unsigned int , unsigned int > > iter(cn->bytes_per_second);
	QVector<int> mdata;

	if (!iter.hasNext())
		return;

	iter.toBack();

	gap_distance = (int)((float)draw_width / TIME_TO_VISUALIZE);
	QPair< unsigned int , unsigned int > data = iter.previous();

	for (i = now; i >= now - TIME_TO_VISUALIZE; i--) {
		if (data.first < i) {
			// no data for time "i"
            if (x_prev != x_pos) {
                y_pos = scale_to_y_axis(0);
                qp->drawLine(x_pos, y_prev, x_prev, y_pos);
            }
		}

		if (data.first == i) {
			if (x_prev != x_pos)
                y_pos = scale_to_y_axis(data.second);
                qp->drawLine(x_pos, y_pos, x_prev, y_pos);
			if (!iter.hasPrevious()) {
				break;
			}
			data = iter.previous();
		}
		y_prev = y_pos;
		x_prev = x_pos;
		x_pos -= gap_distance;
	}
}


void Throughput::drawThroughtputGraphs(QPainter *qp)
{
	unsigned int now = QDateTime::currentDateTime().toTime_t();
	QVector<ConnectionData *> connection_data;

	m_main_window->m_connection_data_mutex.lock();
	connection_data = m_main_window->get_connection_data();

	QVectorIterator<ConnectionData *> i(connection_data);
	while (i.hasNext()) {
		ConnectionData *s = i.next();
		QPen pen(s->color, 3, Qt::SolidLine);
		qp->setPen(pen);
		qp->setRenderHint(QPainter::Antialiasing, true);
		drawThroughputGraph(s, qp, now);
	}
	m_main_window->m_connection_data_mutex.unlock();
}


void Throughput::drawLines(QPainter *qp)
{
	int i;

	draw_width = this->width() - (OUTER_PADDING * 2);
	draw_start_right = this->width() - OUTER_PADDING;

	// background
	qp->setBrush(QBrush("#bbbbbb"));
	qp->drawRect(0, 0, this->width(), this->height());

	// padding from all sides: 40px
	qp->setBrush(QBrush("#999999"));
	qp->drawRect(OUTER_PADDING, OUTER_PADDING, this->width() - OUTER_PADDING * 2,
			this->height() - OUTER_PADDING * 2);


	QPen pen(Qt::black, 1, Qt::DotLine);
	qp->setPen(pen);
	for (i = OUTER_PADDING * 2; i < this->height() - OUTER_PADDING * 2; i += GRID_SPACE) {
		qp->drawLine(OUTER_PADDING, i,  this->width() - OUTER_PADDING, i);
	}
}

