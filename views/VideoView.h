#ifndef VIDEO_H
#define VIDEO_H
#include <QtGui>
#include "../camera/AbstractCamera.h"
class VideoView : public QLabel
{
	Q_OBJECT
public:
	VideoView(QWidget *parent=0);
	AbstractCamera* getCamera();
	~VideoView();
protected:
	virtual void paintEvent(QPaintEvent *ev);
	virtual void resizeEvent(QResizeEvent *ev);
private:
	AbstractCamera *camera;
};

#endif // VIDEO_H
