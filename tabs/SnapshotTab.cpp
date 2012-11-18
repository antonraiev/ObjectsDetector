#include "SnapshotTab.h"
#include "../views/QGraphicsSnapShotItem.h"
#include "../dialogs/SnapshotsDialog.h"
#include "../dialogs/ScenesDialog.h"
#include "../database/DatabaseView.h"
SnapshotTab::SnapshotTab(QWidget *parent)
	: QWidget(parent)
{
	scene=new QGraphicsScene();
	sceneView=new QGraphicsView();
	sceneView->setScene(scene);
	scene->setSceneRect(sceneView->rect());
	slidesScene=new QGraphicsScene();
	slidesView=new SlidesView();
	slidesView->setScene(slidesScene);
	slidesScene->setSceneRect(slidesView->rect());
	slidesView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	slidesView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	slideShift=10;

	// основная сцена
	QVBoxLayout *mainLayout=new QVBoxLayout();
	mainLayout->addWidget(sceneView,3);

	// кнопки
	QHBoxLayout *buttonsLayout=new QHBoxLayout();
	QPushButton *addSnapButton=new QPushButton("Добавить снимок...");
	connect(addSnapButton,SIGNAL(clicked()),SLOT(runSnapshotsDialog()));
	buttonsLayout->addWidget(addSnapButton);

	QPushButton *loadSceneButton=new QPushButton("Загрузить сцену");
	connect(loadSceneButton,SIGNAL(clicked()),SLOT(runScenesDialog()));
	buttonsLayout->addWidget(loadSceneButton);

	QPushButton *sceneBoundsButton=new QPushButton("Пересчитать границы");
	connect(sceneBoundsButton,SIGNAL(clicked()),SLOT(resizeSceneBounds()));
	buttonsLayout->addWidget(sceneBoundsButton);

	QPushButton *fixSceneButton=new QPushButton("Фиксировать сцену");
	connect(fixSceneButton,SIGNAL(clicked()),SLOT(fixScene()));
	buttonsLayout->addWidget(fixSceneButton);

	QPushButton *clearButton=new QPushButton("Очистить");
	QMenu *clearMenu=new QMenu(clearButton);
	clearMenu->addAction("Сцену",this,SLOT(clearScene()));
	clearMenu->addAction("Список",this,SLOT(clearSlidesList()));
	clearMenu->addAction("Все",this,SLOT(clearAll()));
	clearButton->setMenu(clearMenu);

	buttonsLayout->addWidget(clearButton);
	mainLayout->addLayout(buttonsLayout);

	// панель со скриншотами
	rightArrow=new QPushButton(">");
	connect(rightArrow,SIGNAL(clicked()),SLOT(moveSlidesRight()));
	rightArrow->setEnabled(false);
	rightArrow->setMaximumWidth(20);
	rightArrow->setMaximumHeight(300);
	leftArrow=new QPushButton("<");
	connect(leftArrow,SIGNAL(clicked()),SLOT(moveSlidesLeft()));
	leftArrow->setEnabled(false);
	leftArrow->setMaximumWidth(20);
	leftArrow->setMaximumHeight(300);
	QHBoxLayout *slidesLayout=new QHBoxLayout();
	slidesLayout->addWidget(leftArrow,1);
	slidesLayout->addWidget(slidesView,	0);
	slidesLayout->addWidget(rightArrow,1);
	mainLayout->addLayout(slidesLayout,1);
	setLayout(mainLayout);
}
void SnapshotTab::moveSlidesRight()
{
	QRectF slidesRect=slidesView->sceneRect();
	slidesRect.setX(slidesRect.x()+slides.back()->boundingRect().width()+10);
	slidesRect.setWidth(640+slidesRect.x());
	slidesView->setSceneRect(slidesRect);
	if(canShiftedLeft())
		leftArrow->setEnabled(true);
	else leftArrow->setEnabled(false);
	if(canShiftedRight())
		rightArrow->setEnabled(true);
	else rightArrow->setEnabled(false);
}
void SnapshotTab::moveSlidesLeft()
{
	QRectF slidesRect=slidesView->sceneRect();
	slidesRect.setX(slidesRect.x()-slides.back()->boundingRect().width()-10);
	slidesRect.setWidth(640+slidesRect.x());
	slidesView->setSceneRect(slidesRect);
	if(canShiftedLeft())
		leftArrow->setEnabled(true);
	else leftArrow->setEnabled(false);
	if(canShiftedRight())
		rightArrow->setEnabled(true);
	else rightArrow->setEnabled(false);
}
void SnapshotTab::runSnapshotsDialog()
{
	SnapshotsDialog *dialog=new SnapshotsDialog(this);
	DatabaseView dbView;
	dialog->setDbModel(dbView);
	int result=dialog->exec();
	if(result==QDialog::Accepted)
	{
		QList<int> identifiers=dialog->selectedIdentifiers();
		foreach(int id,identifiers)
		{
			addSlide(id);
		}
	}
}
bool SnapshotTab::canShiftedLeft()
{
	double slideLeftBound=scaledSlides.front()->scenePos().x();
	double viewLeftBound=slidesView->sceneRect().x();
	if(slideLeftBound>viewLeftBound)
		return false;
	else return true;
}
bool SnapshotTab::canShiftedRight()
{
	double justx=scaledSlides.back()->scenePos().x();
	double slideRightBound=scaledSlides.back()->pos().x()+scaledSlides.back()->boundingRect().width();
	double slideRightBound2=slides.front()->pos().x()+slides.front()->boundingRect().width();
	double viewRightBound=slidesView->sceneRect().width();
	if(slideRightBound<viewRightBound)
		return false;
	else return true;
}
void SnapshotTab::resizeEvent(QResizeEvent *ev)
{
	scene->setSceneRect(sceneView->rect());
	QWidget::resizeEvent(ev);
}

void SnapshotTab::addSlide(int id)
{
	
	Snapshot snapshot=Database::getInstance().getSnapshot(id);
	
	QGraphicsSnapShotItem *slide=new QGraphicsSnapShotItem();
	slide->setPixmap(QPixmap().fromImage(snapshot.image));
	slide->setId(id);
	slides.push_back(slide);
	drawSlides(1);
}
void SnapshotTab::drawSlides(int n)
{
	if(n!=1)
		return;
	slideShift=10;
	slidesScene->clear();
	scaledSlides.clear();
	for(SlidesList::iterator curSlide=slides.begin(); curSlide!=slides.end(); curSlide++)
	{
		QGraphicsSnapShotItem *slide=new QGraphicsSnapShotItem();
		slide->setPixmap((*curSlide)->pixmap().scaledToHeight(slidesView->mapToScene(slidesView->rect()).boundingRect().height()-20));
		slide->setPos(slideShift,10);
		slideShift=slide->pos().x()+slide->boundingRect().width()+10;
		slidesScene->addItem(slide);
		scaledSlides.push_back(slide);
		slide->setId((*curSlide)->id());
		connect(slide,SIGNAL(doubleClicked(int)),SLOT(addScenePart(int)));
	if(canShiftedLeft())
		leftArrow->setEnabled(true);
	else leftArrow->setEnabled(false);
	if(canShiftedRight())
		rightArrow->setEnabled(true);
	else rightArrow->setEnabled(false);
	}
}
void SnapshotTab::addScenePart(int n)
{
	
	QGraphicsPixmapItem *item=new QGraphicsPixmapItem(QPixmap::fromImage(Database::getInstance().getSnapshot(n).image));
	
	parts.push_back(n);
	scene->addItem(item);
	item->setFlags(QGraphicsItem::ItemIsMovable);
}

void SnapshotTab::runScenesDialog()
{
	ScenesDialog *dialog=new ScenesDialog(this);
	DatabaseView dbView;
	dialog->setDbModel(dbView);
	int result=dialog->exec();
	if(result==QDialog::Accepted)
		addScene(dialog->selectedSceneId());
}

void SnapshotTab::addScene(int id)
{
	
	Scene curScene=Database::getInstance().getScene(id);
	
	scene->clear();
	scene->addPixmap(curScene.pixmap);
	scene->setSceneRect(scene->itemsBoundingRect());                          // Re-shrink the scene to it's bounding contents
}

void SnapshotTab::resizeSceneBounds()
{
	scene->setSceneRect(scene->itemsBoundingRect());
}
void SnapshotTab::fixScene()
{
	QPoint min=QPoint(INT_MAX,INT_MAX),max=QPoint(0,0);
	foreach(QGraphicsItem *item,scene->items())
	{
		if(item->scenePos().x()<=min.x() && item->scenePos().y()<=min.y())
			min=item->scenePos().toPoint();
		if((item->scenePos().x()+item->boundingRect().width())>=max.x() && (item->scenePos().y()+item->boundingRect().height())>=max.y())
			max=QPoint(item->scenePos().x()+item->boundingRect().width(),item->scenePos().y()+item->boundingRect().height());
	}
	QPixmap scenePixmap=QPixmap();

//	scenePixmap=scene.grabWidget(sceneView,QRect(min,max));
scene->clearSelection();                                                  // Selections would also render to the file
scene->setSceneRect(scene->itemsBoundingRect());                          // Re-shrink the scene to it's bounding contents
QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);  // Create the image with the exact size of the shrunk scene
image.fill(Qt::transparent);                                              // Start all pixels transparent

QPainter painter(&image);
scene->render(&painter);
scenePixmap = QPixmap::fromImage(image);
	
	int sceneId=Database::getInstance().addScene(scenePixmap);
	foreach(int snapshot_id,parts)
	{
		Database::getInstance().addPart(sceneId,snapshot_id);
	}
	
	//QLabel *lbl=new QLabel();
	//lbl->setPixmap(scene);
	//lbl->show();
	emit sceneFixed(sceneId);
}
void SnapshotTab::clearScene()
{
	scene->clear();
}
void SnapshotTab::clearSlidesList()
{
	slides.clear();
	scaledSlides.clear();
	slidesScene->clear();
}
void SnapshotTab::clearAll()
{
	clearScene();
	clearSlidesList();
}
SnapshotTab::~SnapshotTab()
{
	delete scene;
	delete slidesScene;
}
