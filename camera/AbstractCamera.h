#pragma once
#include <qobject.h>
#include <qsize.h>

class AbstractCamera : public QObject
{
public:
	virtual void setRenderWidget(QWidget *widget) = 0;
	virtual bool Enabled() = 0;
	virtual bool Run() = 0;
	virtual void Render() = 0;
	virtual bool canRotate() = 0;
	virtual QSize getVideoDimensions() = 0;
};

