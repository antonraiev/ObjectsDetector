#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
    setWindowTitle("Обнаружение объектов");
	QTabWidget *tabs=new QTabWidget();
    vTab = new VideoTab();
    tabs->addTab(vTab,QIcon(":/img/video_icon.jpg"),"Видео");

    mapTab = new MapTab();
    connect(vTab, SIGNAL(factorsChanged(int,QSize,QVector<double>&)),
            mapTab, SLOT(renewMap(int,QSize,QVector<double>&)));
    tabs->addTab(mapTab, QIcon(":/img/map_icon.png"), "Карта");

	QVBoxLayout *layout=new QVBoxLayout();
	layout->addWidget(tabs);
	setLayout(layout);
//	move(x(),y()-100);
	resize(700,400);
}
MainWindow::~MainWindow()
{

}
