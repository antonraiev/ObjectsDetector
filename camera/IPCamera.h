#pragma once
#include <opencv2/core/core.hpp>
#include <highgui.h>
#include <QWidget>
#include <QSize>
#include <string>
#include "AbstractCamera.h"
#include "../cv/QtOpenCV.h"

class IPCamera : public AbstractCamera
{
public:
	IPCamera(void);
	IPCamera(std::string userName, std::string password, std::string ipAddress);
	void setRenderWidget(QWidget *widget);
	bool Enabled();
	bool Run();
	void Render();
	bool canRotate();
	QSize getVideoDimensions();
	virtual ~IPCamera(void);

protected:
	std::string userName;
	std::string password;
	std::string ipAddress;

	cv::VideoCapture capture;
	cv::Mat frame;
	QWidget *videoWidget;
	bool cameraFound;
	QSize dimensions;
};

