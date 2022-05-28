#include "stdafx.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);

	QRect rec = QApplication::desktop()->screenGeometry();
	screenWidth = rec.width();
	screenHeight = rec.height();

	setWindowed();

	p = new QPainter;

	for (int j = -numPoint; j <= numPoint; j++)
	{
		for (int i = -numPoint; i <= numPoint; i++)
		{
			points += QPointF(i * distance, j * distance);
		}
	}

	QTimer *timer = new QTimer(this);
	timer->setTimerType(Qt::PreciseTimer);
	timer->start(timerInterval);

	// timers
	QTimer *radiusTimer = new QTimer(this);
	radiusTimer->setTimerType(Qt::TimerType::PreciseTimer);
	radiusTimer->start(radiusTimerInterval);
	connect(radiusTimer, &QTimer::timeout, this, [=] ()
	{
		radius += dRadius;
		if (radius > maxRadius || radius < minRadius)
		{
			dRadius = -dRadius;
		}
	});

	QTimer *distanceTimer = new QTimer(this);
	distanceTimer->setTimerType(Qt::PreciseTimer);
	distanceTimer->start(radiusTimerInterval);
	connect(distanceTimer, &QTimer::timeout, this, [=] ()
	{
		distance += dDistance;
		if (distance > maxDistance || distance < minDistance)
		{
			dDistance = -dDistance;
		}

		points.clear();
		for (int j = -numPoint; j <= numPoint; j++)
		{
			for (int i = -numPoint; i <= numPoint; i++)
			{
				points += QPointF(i * distance, j * distance);
			}
		}
	});

	QTimer *angleTimer = new QTimer(this);
	angleTimer->setTimerType(Qt::PreciseTimer);
	angleTimer->start(angleTimerInterval);
	connect(angleTimer, &QTimer::timeout, this, [=] ()
	{
		angle += dAngle;
	});

	connect(timer, &QTimer::timeout, this, [=] ()
	{
		p->begin(image);
		p->setRenderHint(QPainter::Antialiasing);

		QTransform transform;
		transform.translate(center.x(), center.y());
		transform.rotate(angle);
		p->setTransform(transform);

		for (int k = 0; k < radius; k++)
		{
			p->setPen(QPen(QColor(qrand() % 256, qrand() % 256, qrand() % 256), 1));
			for (int i = 0; i < points.size(); i++)
			{
				p->drawRect(points[i].x() - k, points[i].y() - k, k * 2, k * 2);
			}
		}
		p->end();
		//ui.m_drawingWidget->setImage( *image );
		ui.label->setPixmap(QPixmap::fromImage(*image));
		frameCounter++;
	});
}

MainWindow::~MainWindow()
{
	delete image;
	delete p;
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		if (this->isFullScreen())
		{
			setWindowed();
		}
		else
		{
			setFullscreeen();
		}
	}
}

// private
void MainWindow::setFullscreeen()
{
	if (image != nullptr)
	{
		delete image;
	}
	image = new QImage(screenWidth, screenHeight, QImage::Format_RGB888);
	image->fill(Qt::white);

	this->showFullScreen();
	ui.label->setGeometry(0, 0, screenWidth, screenHeight);

	center = QPointF(screenWidth / 2, screenHeight / 2);
}
void MainWindow::setWindowed()
{
	if (image != nullptr)
	{
		delete image;
	}
	image = new QImage(windowWidth, windowHeight, QImage::Format_RGB888);
	image->fill(Qt::white);

	this->showNormal();
	ui.label->setGeometry(10, 10, windowWidth, windowHeight);

	center = QPointF(windowWidth / 2, windowHeight / 2);
}