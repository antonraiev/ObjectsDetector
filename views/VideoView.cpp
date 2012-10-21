#include "VideoView.h"
#include "../camera/UsbCamera.h"

VideoView::VideoView(QWidget *parent)
	: QLabel(parent)
{
	camera = new UsbCamera();
	camera->setRenderWidget(this);
	camera->Run();
}
void VideoView::paintEvent(QPaintEvent *ev)
{
	camera->Render();
	this->setMaximumSize(camera->getVideoDimensions());
	QWidget::paintEvent(ev);
}
void VideoView::resizeEvent(QResizeEvent *ev)
{
	QWidget::resizeEvent(ev);
}
AbstractCamera* VideoView::getCamera()
{
	return camera;
}
VideoView::~VideoView()
{
	delete camera;
}