#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("cp1251"));
	setWindowTitle("Обнаружитель объектов");
	QTabWidget *tabs=new QTabWidget();
	vTab = new VideoTab();
	vTab->setDatabase(db);
	tabs->addTab(vTab,QIcon(":/img/video_icon.jpg"),"Видео");

	snapTab = new SnapshotTab();
	snapTab->setDatabase(db);
	connect(vTab,SIGNAL(snapshotAdded(int)),snapTab,SLOT(addSlide(int)));
	tabs->addTab(snapTab,QIcon(":/img/photo_icon.jpg"),"Снимки");
	connect(tabs,SIGNAL(currentChanged(int)),snapTab,SLOT(drawSlides(int)));
	connect(tabs,SIGNAL(currentChanged(int n)),SLOT(drawSlides(int n)));

	sceneTab = new SceneTab();
	sceneTab->setDatabase(db);
	tabs->addTab(sceneTab,QIcon(":/img/scene_icon.png"),"Сцена");
	connect(snapTab,SIGNAL(sceneFixed(int)),sceneTab,SLOT(addScene(int)));

	mapTab = new MapTab();
	mapTab->setDatabase(db);
	connect(sceneTab, SIGNAL(mapCreated(int)), mapTab, SLOT(addMap(int)));
	tabs->addTab(mapTab, QIcon(":/img/map_icon.png"), "Карта");

	dbTab = new DbTab(db);
	tabs->addTab(dbTab,QIcon(":/img/database_icon.png"),"База данных");

	QVBoxLayout *layout=new QVBoxLayout();
	layout->addWidget(tabs);
	setLayout(layout);
	move(x(),y()-100);
	resize(700,400);
}
MainWindow::~MainWindow()
{

}
