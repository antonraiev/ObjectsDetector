#include "videoWidget.h"

videoWidget::videoWidget(QWidget *parent)
	: QLabel(parent)
{
	m_camera.setRenderWidget(this);
	m_camera.Run();
}
void videoWidget::paintEvent(QPaintEvent *ev)
{
	m_camera.Render();
	this->setMaximumSize(m_camera.getVideoDimensions());
	QWidget::paintEvent(ev);
}
void videoWidget::resizeEvent(QResizeEvent *ev)
{
	QWidget::resizeEvent(ev);
}
Camera& videoWidget::camera()
{
	return m_camera;
}
videoWidget::~videoWidget()
{

}