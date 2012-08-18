#include "SceneTab.h"
#include "ScenesDialog.h"
SceneTab::SceneTab(QWidget *parent)
	: QWidget(parent)
{
	scene=new QGraphicsScene();
	sceneView=new QGraphicsView();
	sceneView->setScene(scene);
	scene->setSceneRect(sceneView->rect());
	mainLayout=new QGridLayout();
	mainLayout->addWidget(sceneView,0,0,8,3);
	QPushButton *dialogButton=new QPushButton("Загрузить сцену...");
	connect(dialogButton,SIGNAL(clicked()),SLOT(runScenesDialog()));
	mainLayout->addWidget(dialogButton,8,0,1,1);
	QPushButton *findButton=new QPushButton("Искать объекты");
	connect(findButton,SIGNAL(clicked()),SLOT(find()));
	mainLayout->addWidget(findButton,8,1,1,1);
	QPushButton *mapButton=new QPushButton("Строить карту");
	connect(mapButton,SIGNAL(clicked()),SLOT(buildMap()));
	mainLayout->addWidget(mapButton,8,2,1,1);
	setLayout(mainLayout);
}
void SceneTab::addScene(int id)
{
	db->connect();
	sceneStruct=db->getScene(id);
	db->disconnect();
	scene->clear();
	mapPoints.clear();
	scene->addPixmap(sceneStruct.pixmap);
}
void SceneTab::setDatabase(Database &db)
{
	this->db=&db;
}
void SceneTab::runScenesDialog()
{
	ScenesDialog *dialog=new ScenesDialog(this);
	DatabaseModel dbModel;
	dbModel.setDatabase(*db);
	dialog->setDbModel(dbModel);
	int result=dialog->exec();
	if(result==QDialog::Accepted)
		addScene(dialog->selectedSceneId());
}
void SceneTab::find()
{
	setCursor(Qt::WaitCursor);
	db->connect();
	QList<Object> objects = db->getObjects();
	db->disconnect();
	foreach(Object object, objects)
	{
		QPixmap pixmap = QPixmap::fromImage(object.object);
		QPoint *points = new QPoint[4];
		if(!surf.compare(&sceneStruct.pixmap, &pixmap, points))
		{
			QPen pen;
			if(object.descr.id == ROBOT_ID)
				pen.setColor(Qt::green);
			else
				pen.setColor(Qt::red);
			for(int i=0; i<4; i++)
				scene->addLine(points[i].x(), points[i].y(), points[(i+1)%4].x(), points[(i+1)%4].y(), pen);
			QPoint min = QPoint(1000, 1000), max=QPoint(0, 0);
			for(int i=0; i<4; i++)
			{
				if(sqrt(pow(points[i].x(), 2.) + pow(points[i].y(), 2.)) < sqrt(pow(min.x(), 2.) + pow(min.y(), 2.)) ) 
					min=points[i];
				if(sqrt(pow(points[i].x(), 2.) + pow(points[i].y(), 2.)) > sqrt(pow(max.x(), 2.) + pow(max.y(), 2.)) ) 
					max=points[i];
			}
			QRect rect(min, max);
			mapPoints.insert(make_pair(object.descr.id == ROBOT_ID, rect));
		}
		delete[] points;
	}
	setCursor(Qt::ArrowCursor);
}
void SceneTab::buildMap()
{
	scene->clear();
	for(multimap<bool, QRect>::iterator it = mapPoints.begin(); it!=mapPoints.end(); it++)
		scene->addRect(it->second, it->first ? QPen(Qt::green) : QPen(Qt::red), it->first ? QBrush(Qt::green) : QBrush(Qt::red));
}
void SceneTab::resizeEvent(QResizeEvent *ev)
{
	scene->setSceneRect(sceneView->rect());
	QWidget::resizeEvent(ev);
}
SceneTab::~SceneTab()
{
}
