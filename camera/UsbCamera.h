#pragma once
#include <QtGui>
#include "cv/CvSURF.h"
#include "AbstractCamera.h"

class UsbCamera : public AbstractCamera
{
public:
	UsbCamera(void);
	void setRenderWidget(QWidget *widget);
	bool Enabled();
	bool Run();
	void Render();
	bool canRotate();
	QSize getVideoDimensions();
	virtual ~UsbCamera();
protected:
	static const int defHeight = 0, defWidth = 0;
	CvCapture *capture;
	IplImage *frame;
	QWidget *videoWidget;
	bool cameraFound;
	bool rotateControl;
	QSize dimensions;
};
