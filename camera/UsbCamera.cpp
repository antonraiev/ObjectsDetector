#include "UsbCamera.h"

UsbCamera::UsbCamera(void)
{
    capture = cvCaptureFromCAM(0);
	if(capture == NULL)
	{
		cameraFound = false;
	}
	try
	{
		control = new CMControl();
		rotateControl = true;
	}
	catch(...)
	{
		rotateControl = false;
	}
	//cameraFound = true; //Debug!!
	moveTimer = new QTimer(this);
	QObject::connect(moveTimer,SIGNAL(timeout()),SLOT(moveOnTimer()));
	dimensions = QSize(defWidth,defHeight);
}

void UsbCamera::setRenderWidget(QWidget *widget)
{
	videoWidget = widget;	
}

bool UsbCamera::Run()
{
	return true;
}
void UsbCamera::beginMove(Direction direction)
{
	if(!cameraFound)
		return;
	moveTimer->setInterval(10);
	moveTimer->start();
	moveDirection=direction;
}
void UsbCamera::moveOnTimer()
{
	switch(moveDirection)
	{
	case Up:
		control->Move(0,1); break;
	case Left:
		control->Move(-1,0); break;
	case Down:
		control->Move(0,-1); break;
	case Right:
		control->Move(1,0); break;
	}
}
void UsbCamera::endMove()
{
	if(cameraFound)
		moveTimer->stop();
}
bool UsbCamera::Enabled()
{
	return cameraFound;
}

QSize UsbCamera::getVideoDimensions()
{
	return dimensions;
}
void UsbCamera::Render()
{
	QPainter painter(videoWidget);
    frame = cvQueryFrame(capture); 
    if(frame)
	{
		IplImage *img = cvCloneImage(frame);
		if (img->origin) 
		{
			cvFlip(img);
            img->origin = 0;
        }
        QImage image;
        image = CvSURF::IplCopyToQImage(img);
		if(dimensions == QSize(defWidth, defHeight))
		{
			dimensions.setWidth(image.width());
			dimensions.setHeight(image.height());
		}
		painter.drawImage(0, 0, image);
        cvReleaseImage(&img);
    }
}

bool UsbCamera::canRotate()
{
	return rotateControl;
}

UsbCamera::~UsbCamera()
{
    cvReleaseCapture(&capture);
//	delete control;
}
