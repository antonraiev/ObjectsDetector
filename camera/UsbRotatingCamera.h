#pragma once
#include <QtGui>
#include "CMControl.h"
#include "UsbCamera.h"

class UsbRotatingCamera : public UsbCamera
{
	Q_OBJECT
public:
	enum Direction{Right,Left,Up,Down};
	UsbRotatingCamera(void);
	void beginMove(Direction direction);
	void endMove();
	virtual ~UsbRotatingCamera(void);

protected slots:
	void moveOnTimer();

private:
	Direction moveDirection;
	QTimer *moveTimer;
	CMControl *control;
};

