#pragma once
#include <QtGui>
#pragma comment(lib,"Control.lib")
#pragma comment(lib,"BaseClasses.lib")
#include "MeasureUnit.h"
#include "VideoSource.h"
#include "Controller.h"
#include "CMControl.h"
class Camera : public QObject
{
	Q_OBJECT
public:
	enum Direction{Right,Left,Up,Down};
	Camera(void);
	void setRenderWidget(QWidget *widget);
	bool Enabled();
	bool Run();
	void beginMove(Direction direction);
	void endMove();
	void Render();
	QSize getVideoDimensions();
	~Camera();
protected slots:
	void moveOnTimer();
private:
	static const int defHeight=25;
	static const int defWidth=25;
	CMeasureUnit *unit;
	CCameraVSource camera;
	CMControl *control;
	QTimer *moveTimer;
	Direction moveDirection;
	QWidget *videoWidget;
	bool cameraFound;
	QSize dimensions;
};