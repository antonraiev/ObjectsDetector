#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("cp1251"));
	setWindowTitle("������������ ��������");
	QTabWidget *tabs=new QTabWidget();
	vTab = new VideoTab();
	tabs->addTab(vTab,QIcon(":/img/video_icon.jpg"),"�����");

	snapTab = new SnapshotTab();
	connect(vTab,SIGNAL(snapshotAdded(int)),snapTab,SLOT(addSlide(int)));
	tabs->addTab(snapTab,QIcon(":/img/photo_icon.jpg"),"������");
	connect(tabs,SIGNAL(currentChanged(int)),snapTab,SLOT(drawSlides(int)));
	connect(tabs,SIGNAL(currentChanged(int n)),SLOT(drawSlides(int n)));

	sceneTab = new SceneTab();
	tabs->addTab(sceneTab,QIcon(":/img/scene_icon.png"),"�����");
	connect(snapTab,SIGNAL(sceneFixed(int)),sceneTab,SLOT(addScene(int)));

	mapTab = new MapTab();
	connect(sceneTab, SIGNAL(mapCreated(int)), mapTab, SLOT(addMap(int)));
	tabs->addTab(mapTab, QIcon(":/img/map_icon.png"), "�����");

	dbTab = new DbTab();
	tabs->addTab(dbTab, QIcon(":/img/database_icon.png"),"���� ������");

	QVBoxLayout *layout=new QVBoxLayout();
	layout->addWidget(tabs);
	setLayout(layout);
	move(x(),y()-100);
	resize(700,400);
}
MainWindow::~MainWindow()
{

}
