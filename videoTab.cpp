#include "videoTab.h"
#include <QtSql>
#pragma comment(lib,"Control.lib")
#pragma comment(lib,"BaseClasses.lib")
videoTab::videoTab(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251")); 
	video=new videoWidget();
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
	bool cameraEnabled=video->camera().Enabled();
	//cameraEnabled=true;//Debug!!
	if(!cameraEnabled)
	{
		snap->setEnabled(false);
		leftArrow->setEnabled(false);
		topArrow->setEnabled(false);
		bottomArrow->setEnabled(false);
		rightArrow->setEnabled(false);
	}
	QGridLayout *mainLayout=new QGridLayout();
	QGridLayout *externLayout=new QGridLayout();
	QVBoxLayout *videoLayout=new QVBoxLayout();
	if(cameraEnabled)
	{
		videoLayout->addWidget(video);
	}
	else
	{
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
void videoTab::setDatabase(Database &db)
{
	this->db=&db;
}
void videoTab::takeSnapshot()
{
	QSound sound("Resources/snapshot.wav");
	sound.play();
	QPixmap pixmap;
	pixmap=pixmap.grabWidget(video);
	db->connect();
	int id=db->addSnapshot(pixmap);
	if(id==-1)
		QMessageBox::warning(0,"Ошибка","Ошибка при сохранении снимка в БД");
	else emit snapshotAdded(id);
	db->disconnect();
}
void videoTab::upCameraMove()
{
	video->camera().beginMove(Camera::Up);
}
void videoTab::downCameraMove()
{
	video->camera().beginMove(Camera::Down);
}
void videoTab::leftCameraMove()
{
	video->camera().beginMove(Camera::Left);
}
void videoTab::rightCameraMove()
{
	video->camera().beginMove(Camera::Right);
}
void videoTab::endCameraMove()
{
	video->camera().endMove();
}
void videoTab::paintEvent(QPaintEvent *ev)
{
	QPainter painter(this);
}

videoTab::~videoTab()
{
}
