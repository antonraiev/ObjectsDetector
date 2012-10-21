#include "UsbRotatingCamera.h"


UsbRotatingCamera::UsbRotatingCamera(void)
{
	try
	{
		control = new CMControl();
		rotateControl = true;
	}
	catch(...)
	{
		rotateControl = false;
	}
	moveTimer = new QTimer(this);
	QObject::connect(moveTimer,SIGNAL(timeout()),SLOT(moveOnTimer()));
}

void UsbRotatingCamera::beginMove(Direction direction)
{
	if(!cameraFound || !rotateControl)
		return;
	moveTimer->setInterval(10);
	moveTimer->start();
	moveDirection=direction;
}
void UsbRotatingCamera::moveOnTimer()
{
	switch(moveDirection)
	{
	case Up:
		control->Move(0,1); break;
	case Left:
		control->Move(-1,0); break;
	case Down:
		control->Move(0,-1); break;
	case Right:
		control->Move(1,0); break;
	}
}
void UsbRotatingCamera::endMove()
{
	if(!cameraFound || !rotateControl)
	{
		return;
	}
	moveTimer->stop();
}

UsbRotatingCamera::~UsbRotatingCamera(void)
{
	if(rotateControl)
	{
		delete control;
	}
}
