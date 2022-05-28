#pragma once

#include "ui_mainwindow.h"

class MainWindow : public QWidget {
	Q_OBJECT

public:
	MainWindow( QWidget *parent = Q_NULLPTR );
	~MainWindow();

protected:
	virtual void mouseDoubleClickEvent( QMouseEvent *e );

private:
	void setFullscreeen();
	void setWindowed();

	Ui::MainWindowClass ui;

	int screenWidth = 0;
	int screenHeight = 0;
	int windowWidth = 300;
	int windowHeight = 300;
	int numPoint = 5;
	QVector< QPointF > points;

	QPointF center;

	int timerInterval = 0;
	int radiusTimerInterval = 0;
	int distanceTimerInterval = 0;
	int angleTimerInterval = 0;

	double radius = 15.0;
	double minRadius = 10.0;
	double maxRadius = 20.0;
	double dRadius = 1.0;

	double distance = 0.0;
	double minDistance = 0.0;
	double maxDistance = 200.0;
	double dDistance = 0.1;

	double angle = 0.0;
	double dAngle = 1.0;

	QImage *image = nullptr;
	QPainter *p = nullptr;

	int frameCounter = 0;
};
