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
			for(int i=0; i<4; i++)
				scene->addLine(points[i].x(), points[i].y(), points[(i+1)%4].x(), points[(i+1)%4].y(), QPen(Qt::red));
		}
		QPoint min = QPoint(INT_MAX, INT_MAX), max=QPoint(0, 0);
		for(int i=0; i<4; i++)
		{
			if(points[i].x()<=min.x() && points[i].y()<=min.y())
				min=points[i];
			if(points[i].x()>=max.x() && points[i].y()>=max.y())
				max=points[i];
		}
		delete[] points;
	}
	setCursor(Qt::ArrowCursor);
}
void SceneTab::buildMap()
{

}
void SceneTab::resizeEvent(QResizeEvent *ev)
{
	scene->setSceneRect(sceneView->rect());
	QWidget::resizeEvent(ev);
}
SceneTab::~SceneTab()
{
}
