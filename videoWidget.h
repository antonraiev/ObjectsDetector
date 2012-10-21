#ifndef VIDEO_H
#define VIDEO_H
#include <QtGui>
#include "AbstractCamera.h"
class videoWidget : public QLabel
{
	Q_OBJECT
public:
	videoWidget(QWidget *parent=0);
	AbstractCamera* getCamera();
	~videoWidget();
protected:
	virtual void paintEvent(QPaintEvent *ev);
	virtual void resizeEvent(QResizeEvent *ev);
private:
	AbstractCamera *camera;
};

#endif // VIDEO_H
