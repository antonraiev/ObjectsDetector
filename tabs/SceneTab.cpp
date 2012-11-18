#include "SceneTab.h"
#include "../dialogs/ScenesDialog.h"
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
	
	currentScene=db->getScene(id);
	
	scene->clear();
	mapPoints.clear();
	scene->addPixmap(currentScene.pixmap);
	// Re-shrink the scene to it's bounding contents
	scene->setSceneRect(scene->itemsBoundingRect());                          
}
void SceneTab::setDatabase(Database &db)
{
	this->db = &db;
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
	
	QList<Object> objects = db->getObjects();
	
	sift.setScene(currentScene.pixmap.toImage());
	foreach(Object object, objects)
	{
		QPixmap pixmap = QPixmap::fromImage(object.object);
//		QPoint *points = new QPoint[4];
		QGraphicsRectItem *rectItem;
//		if(!surf.compare(&currentScene.pixmap, &pixmap, points))
		SiftResult result = sift.doSIFT(/*currentScene.pixmap.toImage(), */pixmap.toImage());
		if(result.isHomographyFound)
		{
			QPen pen;
			if(object.descr.id == ROBOT_ID)
				pen.setColor(Qt::green);
			else
				pen.setColor(Qt::red);
			result.rectItem->setPen(pen);
			QRectF rectf = result.rectItem->rect();
			scene->addItem(result.rectItem);
//			for(int i=0; i<4; i++)
//				scene->addLine(points[i].x(), points[i].y(), points[(i+1)%4].x(), points[(i+1)%4].y(), pen);
			
			//QPoint min = QPoint(1000, 1000), max=QPoint(0, 0);
			//for(int i=0; i<4; i++)
			//{
			//	if(sqrt(pow(points[i].x(), 2.) + pow(points[i].y(), 2.)) < sqrt(pow(min.x(), 2.) + pow(min.y(), 2.)) ) 
			//		min=points[i];
			//	if(sqrt(pow(points[i].x(), 2.) + pow(points[i].y(), 2.)) > sqrt(pow(max.x(), 2.) + pow(max.y(), 2.)) ) 
			//		max=points[i];
			//}
			QPointF topLeft = result.rectItem->scenePos();
			QPoint min = QPoint(topLeft.x(), topLeft.y()), 
				   max = QPoint(topLeft.x() + result.rectItem->rect().width(), topLeft.y() + result.rectItem->rect().height());
			QRect rect(min, max);
			mapPoints.insert(make_pair(object.descr.id == ROBOT_ID, rect));
			if(object.descr.id == ROBOT_ID)
			{
				robotHeightPx = max.y() - min.y();
				robotHeightSm = object.phys_height;
			}
		}
		//delete[] points;
	}
	setCursor(Qt::ArrowCursor);
}
void SceneTab::buildMap()
{
	QGraphicsScene *mapScene = new QGraphicsScene();
	double scale = robotHeightPx / robotHeightSm;
	for(multimap<bool, QRect>::iterator it = mapPoints.begin(); it!=mapPoints.end(); it++)
	{
		QRect objectRect = it->second;
		bool isRobot = it->first;
		mapScene->addRect(objectRect.x() / scale, objectRect.y() / scale, 
			objectRect.width() / scale, objectRect.height() / scale,
			isRobot ? QPen(Qt::green) : QPen(Qt::red), 
			isRobot ? QBrush(Qt::green) : QBrush(Qt::red));
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

	// Selections would also render to the file
	mapScene->clearSelection();
	// Re-shrink the scene to it's bounding contents
	mapScene->setSceneRect(scene->itemsBoundingRect());
	// Create the image with the exact size of the shrunk scene
	QImage image(mapScene->sceneRect().size().toSize(), QImage::Format_ARGB32);  
	image.fill(Qt::transparent);                                              

	QPainter painter(&image);
	mapScene->render(&painter);
	QPixmap pixmap = QPixmap::fromImage(image);
	
	int mapId = db->addMap(pixmap);
	
	emit mapCreated(mapId);
	delete mapScene;
}
void SceneTab::resizeEvent(QResizeEvent *ev)
{
	scene->setSceneRect(sceneView->rect());
	QWidget::resizeEvent(ev);
}
SceneTab::~SceneTab()
{
}
