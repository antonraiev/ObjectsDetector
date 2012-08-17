#include "camera.h"

Camera::Camera(void)
{
	unit=new CMeasureUnit();
	unit->SetController(NULL);
	unit->SetEtalonColor(0x00ffffff);
	try
	{
		control=new CMControl();
		cameraFound=true;
	}
	catch(...)
	{
		cameraFound=false;
//		QMessageBox::warning(NULL,"Ошибка","Устройство не найдено.\n Программа будет работать\n"\
//			" в автономном режиме.");
	}
	cameraFound=true; //Debug!!
	moveTimer=new QTimer(this);
	QObject::connect(moveTimer,SIGNAL(timeout()),SLOT(moveOnTimer()));
	dimensions=QSize(defWidth,defHeight);
}

void Camera::setRenderWidget(QWidget *widget)
{
	RECT rect;
	rect.bottom=widget->rect().bottom();
	rect.right=widget->rect().right();
	rect.left=widget->rect().left();
	rect.top=widget->rect().top();
	unit->SetRenderWnd(widget->winId(),rect);
	videoWidget=widget;
	
}

bool Camera::Run()
{
	if(!camera.Init(TRUE,unit))
		return false;
	if(!camera.Run())
		return false;
	return true;
}
void Camera::beginMove(Direction direction)
{
	if(!cameraFound)
		return;
	moveTimer->setInterval(10);
	moveTimer->start();
	moveDirection=direction;
}
void Camera::moveOnTimer()
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
void Camera::endMove()
{
	if(cameraFound)
		moveTimer->stop();
}
bool Camera::Enabled()
{
	return cameraFound;
}

QSize Camera::getVideoDimensions()
{
	return dimensions;
}
void Camera::Render()
{
	QPainter painter(videoWidget);
	BITMAPINFO bmi;
	PBYTE data = unit->LockResBuffer(&bmi);
	if(data)
	{	
		QImage::Format fmt = QImage::Format_RGB32;
		switch(bmi.bmiHeader.biBitCount)
		{
		case 16:
			fmt = QImage::Format_RGB555;
			break;
		case 24:
			fmt = QImage::Format_RGB888;
			break;
		case 32:
			fmt = QImage::Format_RGB32;
			break;
		}
		if(dimensions==QSize(defWidth,defHeight))
		{
			dimensions.setWidth(bmi.bmiHeader.biWidth);
			dimensions.setHeight(bmi.bmiHeader.biHeight);
		}
		QImage img(data, bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight, fmt);
		painter.drawImage(0, 0, img.rgbSwapped().mirrored());
		unit->UnLockResBuffer();
	}
}

Camera::~Camera()
{
	camera.Stop();
	delete unit;
//	delete control;
}
