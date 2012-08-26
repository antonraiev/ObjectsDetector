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
	connect(findButton,SIGNAL(clicked()),SLOT(saveMapToFile()));
	mainLayout->addWidget(findButton,8,2,1,1);
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
void MapTab::saveMapToFile()
{
	const QRgb OBSTACLE_COLOR = qRgb(255, 0, 0),
			   ROBOT_COLOR	  = qRgb(0, 255, 0);
	const char FREE_AREA_SYM	  = '0',
			   ROBOT_AREA_SYM	  = '2',
			   OBSTACLE_AREA_SYM  = '1';
	QString fileName = QFileDialog::getSaveFileName(this, "Сохранить карту как:", QDir::currentPath(), "*.txt");
	QFile file(fileName);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream mapFileStream(&file);
	mapFileStream << currentMap.image.width() << " " << currentMap.image.height() << "\n";
	for(int i = 0; i<currentMap.image.height(); i++)
	{
		for(int j = 0; j<currentMap.image.width(); j++)
		{
			if(currentMap.image.pixel(j, i) == OBSTACLE_COLOR)
				mapFileStream << OBSTACLE_AREA_SYM;
			else if(currentMap.image.pixel(j, i) == ROBOT_COLOR)
				mapFileStream << ROBOT_AREA_SYM;
			else
				mapFileStream << FREE_AREA_SYM;
		}
		mapFileStream << "\n";
	}
	file.close();
}
void MapTab::resizeEvent(QResizeEvent *ev)
{
	scene->setSceneRect(sceneView->rect());
	QWidget::resizeEvent(ev);
}
MapTab::~MapTab()
{
}
