#include "videoWidget.h"
#include "UsbCamera.h"
videoWidget::videoWidget(QWidget *parent)
	: QLabel(parent)
{
	camera = new UsbCamera();
	camera->setRenderWidget(this);
	camera->Run();
}
void videoWidget::paintEvent(QPaintEvent *ev)
{
	camera->Render();
	this->setMaximumSize(camera->getVideoDimensions());
	QWidget::paintEvent(ev);
}
void videoWidget::resizeEvent(QResizeEvent *ev)
{
	QWidget::resizeEvent(ev);
}
AbstractCamera* videoWidget::getCamera()
{
	return camera;
}
videoWidget::~videoWidget()
{
	delete camera;
}