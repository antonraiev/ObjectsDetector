#ifndef VIDEO_H
#define VIDEO_H
#include <QtGui>
#include "camera.h"
class videoWidget : public QLabel
{
	Q_OBJECT
public:
	videoWidget(QWidget *parent=0);
	Camera& camera();
	~videoWidget();
protected:
	virtual void paintEvent(QPaintEvent *ev);
	virtual void resizeEvent(QResizeEvent *ev);
private:
	Camera m_camera;
};

#endif // VIDEO_H
