#pragma once
#include <QtGui>
#include "../cv/CvSURF.h"
#include "CMControl.h"
#include "AbstractCamera.h"

class UsbCamera : public AbstractCamera
{
	Q_OBJECT
public:
	enum Direction{Right,Left,Up,Down};
	UsbCamera(void);
	void setRenderWidget(QWidget *widget);
	bool Enabled();
	bool Run();
	void beginMove(Direction direction);
	void endMove();
	void Render();
	bool canRotate();
	QSize getVideoDimensions();
	~UsbCamera();
protected slots:
	void moveOnTimer();
private:
	static const int defHeight = 0;
	static const int defWidth = 0;
	CvCapture *capture;
	IplImage *frame;
	CMControl *control;
	QTimer *moveTimer;
	Direction moveDirection;
	QWidget *videoWidget;
	bool cameraFound;
	bool rotateControl;
	QSize dimensions;
};