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
	connect(findButton,SIGNAL(clicked()),SLOT(findObjects()));
	mainLayout->addWidget(findButton,8,1,1,1);
	QPushButton *mapButton=new QPushButton("Строить карту");
	connect(mapButton,SIGNAL(clicked()),SLOT(buildMap()));
	mainLayout->addWidget(mapButton,8,2,1,1);
	setLayout(mainLayout);
}
void SceneTab::addScene(int id)
{
	db->connect();
	currentScene=db->getScene(id);
	db->disconnect();
	scene->clear();
	mapPoints.clear();
	scene->addPixmap(currentScene.pixmap);
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
void SceneTab::findObjects()
{
	setCursor(Qt::WaitCursor);
	db->connect();
	QList<Object> objects = db->getObjects();
	db->disconnect();
	foreach(Object object, objects)
	{
		QPixmap pixmap = QPixmap::fromImage(object.object);
		QPoint *points = new QPoint[4];
		if(!surf.compare(&currentScene.pixmap, &pixmap, points))
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
			if(object.descr.id == ROBOT_ID)
			{
				robotHeightPx = max.y() - min.y();
				robotHeightSm = object.phys_height;
			}
		}
		delete[] points;
	}
	setCursor(Qt::ArrowCursor);
}
void SceneTab::buildMap()
{
	scene->clear();
	double scale = robotHeightPx / robotHeightSm;
	for(multimap<bool, QRect>::iterator it = mapPoints.begin(); it!=mapPoints.end(); it++)
	{
		QRect objectRect = it->second;
		bool isRobot = it->first;
		scene->addRect(objectRect.x() / scale, objectRect.y() / scale, objectRect.width() / scale, objectRect.height() / scale,
			isRobot ? QPen(Qt::green) : QPen(Qt::red), isRobot ? QBrush(Qt::green) : QBrush(Qt::red));
	}
	int maxX = 0, maxY = 0;
	for(multimap<bool, QRect>::iterator it = mapPoints.begin(); it!=mapPoints.end(); it++)
	{
		QRect objectRect = it->second;
		if(objectRect.x() / scale + objectRect.width() / scale > maxX)
			maxX = objectRect.x() / scale + objectRect.width() / scale;
		if(objectRect.y() / scale + objectRect.height() / scale > maxY)
			maxY = objectRect.y() / scale + objectRect.height() / scale;
	}

	QPixmap pixmap = QPixmap::grabWidget(sceneView, 0, 0, maxX, maxY);
	db->connect();
	int mapId = db->addMap(pixmap);
	db->disconnect();
	scene->clear();
	scene->addPixmap(currentScene.pixmap);
	emit mapCreated(mapId);
}
void SceneTab::resizeEvent(QResizeEvent *ev)
{
	scene->setSceneRect(sceneView->rect());
	QWidget::resizeEvent(ev);
}
SceneTab::~SceneTab()
{
}
