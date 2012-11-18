#include "VideoTab.h"
#include <QtSql>
#include "../camera/UsbRotatingCamera.h"
#pragma comment(lib,"Control.lib")

VideoTab::VideoTab(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251")); 
	video = new VideoView();
	QTimer* videoTimer = new QTimer(this);
	connect(videoTimer, SIGNAL(timeout()), video, SLOT(repaint()));
	videoTimer->setInterval(10);
	videoTimer->start();
	QPushButton *snap=new QPushButton("Снимок");
	QPushButton *leftArrow=new QPushButton(QIcon(":/img/leftarrow.jpg"),"");
	QPushButton *topArrow=new QPushButton(QIcon(":/img/toparrow.jpg"),"");
	QPushButton *bottomArrow=new QPushButton(QIcon(":/img/bottomarrow.jpg"),"");
	QPushButton *rightArrow=new QPushButton(QIcon(":/img/rightarrow.jpg"),"");
	leftArrow->setMaximumWidth(50);
	topArrow->setMaximumWidth(50);
	bottomArrow->setMaximumWidth(50);
	rightArrow->setMaximumWidth(50);
	connect(rightArrow,SIGNAL(pressed()),SLOT(rightCameraMove()));
	connect(leftArrow,SIGNAL(pressed()),SLOT(leftCameraMove()));
	connect(topArrow,SIGNAL(pressed()),SLOT(upCameraMove()));
	connect(bottomArrow,SIGNAL(pressed()),SLOT(downCameraMove()));
	connect(rightArrow,SIGNAL(released()),SLOT(endCameraMove()));
	connect(leftArrow,SIGNAL(released()),SLOT(endCameraMove()));
	connect(topArrow,SIGNAL(released()),SLOT(endCameraMove()));
	connect(bottomArrow,SIGNAL(released()),SLOT(endCameraMove()));
	QGridLayout *gridArrows=new QGridLayout;
	gridArrows->addWidget(leftArrow,1,0,1,1);
	gridArrows->addWidget(topArrow,0,1,1,1);
	gridArrows->addWidget(rightArrow,1,2,1,1);
	gridArrows->addWidget(bottomArrow,2,1,1,1,Qt::AlignTop);
	QGroupBox *controlGroup=new QGroupBox("Управление поворотами:");
	controlGroup->setLayout(gridArrows);
	connect(snap,SIGNAL(clicked()),SLOT(takeSnapshot()));
	bool canRotate = video->getCamera()->canRotate();
	//cameraEnabled=true;//Debug!!
	if(!canRotate)
	{
		leftArrow->setEnabled(false);
		topArrow->setEnabled(false);
		bottomArrow->setEnabled(false);
		rightArrow->setEnabled(false);
	}
	QGridLayout *mainLayout=new QGridLayout();
	QGridLayout *externLayout=new QGridLayout();
	QVBoxLayout *videoLayout=new QVBoxLayout();
	if(video->getCamera()->Enabled())
	{
		videoLayout->addWidget(video);
	}
	else
	{
		snap->setEnabled(false);
		QLabel *noVideo=new QLabel();
		QPalette palette;
		palette.setBrush(noVideo->backgroundRole(),QBrush(Qt::black));
		palette.setColor(QPalette::WindowText,Qt::white);
		noVideo->setPalette(palette);
		noVideo->setAutoFillBackground(true);
		noVideo->setText("Видео недоступно");
		noVideo->setAlignment(Qt::AlignCenter);
		videoLayout->addWidget(noVideo);
	}
	externLayout->addLayout(videoLayout,0,0);
	mainLayout->addLayout(externLayout,0,0,3,3);
	mainLayout->addWidget(controlGroup,0,3,1,1);
	mainLayout->addWidget(snap,1,3,1,1);
	setLayout(mainLayout);
}

void VideoTab::takeSnapshot()
{
	QSound sound("Resources/snapshot.wav");
	sound.play();
	QPixmap pixmap;
	pixmap = pixmap.grabWidget(video);
	
	int id = 0;
	try
	{
		id = Database::getInstance().addSnapshot(pixmap);
	}
	catch(DbException ex)
	{
		QMessageBox::warning(0,"Ошибка", ex.what());
		return;
	}
	emit snapshotAdded(id);
}
void VideoTab::upCameraMove()
{
	dynamic_cast<UsbRotatingCamera*>(video->getCamera())->beginMove(UsbRotatingCamera::Up);
}
void VideoTab::downCameraMove()
{
	dynamic_cast<UsbRotatingCamera*>(video->getCamera())->beginMove(UsbRotatingCamera::Down);
}
void VideoTab::leftCameraMove()
{
	dynamic_cast<UsbRotatingCamera*>(video->getCamera())->beginMove(UsbRotatingCamera::Left);
}
void VideoTab::rightCameraMove()
{
	dynamic_cast<UsbRotatingCamera*>(video->getCamera())->beginMove(UsbRotatingCamera::Right);
}
void VideoTab::endCameraMove()
{
	dynamic_cast<UsbRotatingCamera*>(video->getCamera())->endMove();
}
void VideoTab::paintEvent(QPaintEvent *ev)
{
	QPainter painter(this);
}

VideoTab::~VideoTab()
{
}
