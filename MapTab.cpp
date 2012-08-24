#include "MapTab.h"
#include "ScenesDialog.h"
MapTab::MapTab(QWidget *parent)
	: QWidget(parent)
{
	scene=new QGraphicsScene();
	sceneView=new QGraphicsView();
	sceneView->setScene(scene);
	scene->setSceneRect(sceneView->rect());
	mainLayout=new QGridLayout();
	mainLayout->addWidget(sceneView,0,0,8,3);

	QPushButton *dialogButton=new QPushButton("Загрузить карту...");
	connect(dialogButton,SIGNAL(clicked()),SLOT(runMapsDialog()));
	mainLayout->addWidget(dialogButton,8,1,1,1);

	QPushButton *findButton=new QPushButton("Сохранить в файл...");
	connect(findButton,SIGNAL(clicked()),SLOT(saveMap()));
	mainLayout->addWidget(findButton,8,2,1,1);

//	QPushButton *mapButton=new QPushButton("Очистить");
//	connect(mapButton,SIGNAL(clicked()),SLOT(clear()));
//	mainLayout->addWidget(mapButton,8,2,1,1);
	setLayout(mainLayout);
}
void MapTab::addMap(int id)
{
	db->connect();
	currentMap = db->getMap(id);
	db->disconnect();
	scene->clear();
	scene->addPixmap(QPixmap::fromImage(currentMap.image));
}
void MapTab::setDatabase(Database &db)
{
	this->db=&db;
}
void MapTab::runMapsDialog()
{
	ScenesDialog *dialog=new ScenesDialog(this);
	DatabaseModel dbModel;
	dbModel.setDatabase(*db);
	dialog->setDbModel(dbModel);
	int result=dialog->exec();
	if(result==QDialog::Accepted)
		addMap(dialog->selectedSceneId());
}
void MapTab::saveMap()
{
}
void MapTab::resizeEvent(QResizeEvent *ev)
{
	scene->setSceneRect(sceneView->rect());
	QWidget::resizeEvent(ev);
}
MapTab::~MapTab()
{
}
