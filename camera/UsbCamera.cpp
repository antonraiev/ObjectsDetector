#include "UsbCamera.h"

UsbCamera::UsbCamera(void)
{
	dimensions = QSize(defWidth,defHeight);
	rotateControl = false;
}

void UsbCamera::setRenderWidget(QWidget *widget)
{
	videoWidget = widget;	
}

bool UsbCamera::Run()
{
    capture = cvCaptureFromCAM(0);
	if(capture == NULL)
	{
		cameraFound = false;
		return cameraFound;
	}
	return true;
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
}
