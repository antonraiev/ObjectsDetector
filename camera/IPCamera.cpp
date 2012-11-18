#include <QPainter>
#include <QImage>
#include "IPCamera.h"

IPCamera::IPCamera(void)
{
	userName = "";
	password = "";
	ipAddress = "192.168.0.20";
	dimensions = QSize(0, 0);
}

IPCamera::IPCamera(std::string userName, std::string password, std::string ipAddress)
{
	this->userName = userName;
	this->password = password;
	this->ipAddress = ipAddress;
}

void IPCamera::setRenderWidget(QWidget *widget)
{
	videoWidget = widget;
}

bool IPCamera::Enabled()
{
	return cameraFound;
}

bool IPCamera::Run()
{
//    std::string videoStreamAddress = "http://" + userName + ":" + password 
//									 + "@" + ipAddress + "/video.cgi?.mjpg";
	std::string videoStreamAddress = "http://192.168.0.20/video.cgi?.mjpg";
    if(!capture.open(videoStreamAddress)) 
	{
		cameraFound = false;
        return cameraFound;
	}
	cameraFound = true;
	return cameraFound;
}

void IPCamera::Render()
{
	QPainter painter(videoWidget);
    if(!capture.read(frame)) 
	{
		return;
    }
	QImage image = cvtCvMat2QImage(frame);
	if(dimensions == QSize(0, 0))
	{
		dimensions.setWidth(image.width());
		dimensions.setHeight(image.height());
	}
	painter.drawImage(0, 0, image);
	frame.release();
}

bool IPCamera::canRotate()
{
	return false;
}

QSize IPCamera::getVideoDimensions()
{
	return dimensions;
}

IPCamera::~IPCamera(void)
{
}
