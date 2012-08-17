#include "mainWindow.h"

mainWindow::mainWindow(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("cp1251"));
	setWindowTitle("������������ ��������");
	QTabWidget *tabs=new QTabWidget();
	vTab=new videoTab();
	vTab->setDatabase(db);
	tabs->addTab(vTab,QIcon(":/img/video_icon.jpg"),"�����");

	snapTab=new snapShotTab();
	snapTab->setDatabase(db);
	connect(vTab,SIGNAL(snapshotAdded(int)),snapTab,SLOT(addSlide(int)));
	tabs->addTab(snapTab,QIcon(":/img/photo_icon.jpg"),"������");
	connect(tabs,SIGNAL(currentChanged(int)),snapTab,SLOT(drawSlides(int)));
	connect(tabs,SIGNAL(currentChanged(int n)),SLOT(drawSlides(int n)));
	sceneTab=new SceneTab();
	sceneTab->setDatabase(db);
	tabs->addTab(sceneTab,QIcon(":/img/scene_icon.png"),"�����");
	connect(snapTab,SIGNAL(sceneFixed(int)),sceneTab,SLOT(addScene(int)));
	dbTab=new DbTab(db);
	tabs->addTab(dbTab,QIcon(":/img/database_icon.png"),"���� ������");

	QVBoxLayout *layout=new QVBoxLayout();
	layout->addWidget(tabs);
	setLayout(layout);
	move(x(),y()-100);
	resize(700,400);
}
mainWindow::~mainWindow()
{

}
