#include "MapTab.h"
#include "../dialogs/ScenesDialog.h"
#include <QtGui>

MapTab::MapTab(QWidget *parent)
	: QWidget(parent)
{
	scene=new QGraphicsScene();
	sceneView=new QGraphicsView();
	sceneView->setScene(scene);
	scene->setSceneRect(sceneView->rect());
	mainLayout=new QGridLayout();
	mainLayout->addWidget(sceneView,0,0,8,3);

	QPushButton *sendButton=new QPushButton("Отправить");
	connect(sendButton,SIGNAL(clicked()),SLOT(sendToKate()));
	mainLayout->addWidget(sendButton,8,0,1,1);

	QPushButton *dialogButton=new QPushButton("Загрузить карту...");
	connect(dialogButton,SIGNAL(clicked()),SLOT(runMapsDialog()));
	mainLayout->addWidget(dialogButton,8,1,1,1);

	QPushButton *findButton=new QPushButton("Сохранить в файл...");
	connect(findButton,SIGNAL(clicked()),SLOT(saveMapToFile()));
	mainLayout->addWidget(findButton,8,2,1,1);

	fuzzyGrid = new FuzzyGrid(scene);
	QGroupBox *fuzzyControls = new QGroupBox("Нечеткая логика:");	
	QGridLayout *fuzzyLayout = new QGridLayout();
	QCheckBox *showGridBox = new QCheckBox("Отображать сетку");
	connect(showGridBox, SIGNAL(stateChanged(int)), fuzzyGrid, SLOT(showGrid(int)));
	fuzzyLayout->addWidget(showGridBox, 0, 0, 1, 1);
	QLabel *gridSizeLabel = new QLabel("Размер сетки:");
	fuzzyLayout->addWidget(gridSizeLabel, 1, 0, 1, 1);
	QRadioButton *oneSize = new QRadioButton("1");
	QRadioButton *twoSize = new QRadioButton("2");
	QRadioButton *fourSize = new QRadioButton("4");
	oneSize->setChecked(true);
	fuzzyLayout->addWidget(oneSize, 2, 0, 1, 1);
	fuzzyLayout->addWidget(twoSize, 3, 0, 1, 1);
	fuzzyLayout->addWidget(fourSize, 4, 0, 1, 1);
	QPushButton *calcButton = new QPushButton("Выполнить расчет");
	connect(calcButton, SIGNAL(clicked()), fuzzyGrid, SLOT(doCalculations()));
	fuzzyLayout->addWidget(calcButton, 5, 0, 1, 1);
	
	fuzzyControls->setLayout(fuzzyLayout);

	mainLayout->addWidget(fuzzyControls, 0, 3, 1, 1);
	setLayout(mainLayout);
}
void MapTab::addMap(int id)
{
	
	currentMap = Database::getInstance().getMap(id);
	
	scene->clear();
	scene->addPixmap(QPixmap::fromImage(currentMap.image));
}

void MapTab::runMapsDialog()
{
	ScenesDialog *dialog=new ScenesDialog(this);
	DatabaseView dbView;
	dialog->setDbModel(dbView);
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
void MapTab::sendToKate()
{
	kateSocket = new QTcpSocket(this);
	connect(kateSocket, SIGNAL(connected()), SLOT(connectedToKate()));
	connect(kateSocket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(errorToKate(QAbstractSocket::SocketError)));
//	kateSocket->connectToHost("5.183.186.121", 2005);
	kateSocket->connectToHost("192.168.216.174", 2005);
}
void MapTab::connectedToKate()
{
	QString sendString = "";
	const QRgb OBSTACLE_COLOR = qRgb(255, 0, 0),
			   ROBOT_COLOR	  = qRgb(0, 255, 0);
	const char FREE_AREA_SYM	  = '0',
			   ROBOT_AREA_SYM	  = '2',
			   OBSTACLE_AREA_SYM  = '1';
	sendString += QString::number(currentMap.image.width()) + " " + QString::number(currentMap.image.height()) + " ";
	for(int i = 0; i<currentMap.image.height(); i++)
	{
		for(int j = 0; j<currentMap.image.width(); j++)
		{
			if(currentMap.image.pixel(j, i) == OBSTACLE_COLOR)
				sendString += OBSTACLE_AREA_SYM;
			else if(currentMap.image.pixel(j, i) == ROBOT_COLOR)
				sendString += ROBOT_AREA_SYM;
			else
				sendString += FREE_AREA_SYM;
		}
	}
	sendString += "\n";
	QTextStream out(&sendString, QIODevice::WriteOnly);
	QByteArray byteArray = sendString.toAscii();
	const char *sendCString = byteArray.data();
	kateSocket->write(sendCString);
	kateSocket->flush();
	kateSocket->close();
}
void MapTab::errorToKate(QAbstractSocket::SocketError error)
{
}
void MapTab::resizeEvent(QResizeEvent *ev)
{
	scene->setSceneRect(sceneView->rect());
	QWidget::resizeEvent(ev);
}

void MapTab::wheelEvent(QWheelEvent *ev)
{
	double scaleStep = ev->delta() / 120;
	sceneView->scale(scaleStep, scaleStep);
}

void MapTab::keyPressEvent(QKeyEvent *ev)
{
	if(ev->key() == Qt::Key_Plus)
	{
		sceneView->scale(1.2, 1.2);
		scene->setSceneRect(scene->itemsBoundingRect());
	}
	else if(ev->key() == Qt::Key_Minus)
	{
		sceneView->scale(0.8, 0.8);
		scene->setSceneRect(scene->itemsBoundingRect());
	}
}
MapTab::~MapTab()
{
}
