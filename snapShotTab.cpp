#include "snapShotTab.h"
#include "QGraphicsSnapShotItem.h"
#include "SnapshotsDialog.h"
#include "DatabaseModel.h"
snapShotTab::snapShotTab(QWidget *parent)
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
void snapShotTab::moveSlidesRight()
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
void snapShotTab::moveSlidesLeft()
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
void snapShotTab::runSnapshotsDialog()
{
	SnapshotsDialog *dialog=new SnapshotsDialog(this);
	DatabaseModel dbModel;
	dbModel.setDatabase(*db);
	dialog->setDbModel(dbModel);
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
bool snapShotTab::canShiftedLeft()
{
	double slideLeftBound=scaledSlides.front()->scenePos().x();
	double viewLeftBound=slidesView->sceneRect().x();
	if(slideLeftBound>viewLeftBound)
		return false;
	else return true;
}
bool snapShotTab::canShiftedRight()
{
	double justx=scaledSlides.back()->scenePos().x();
	double slideRightBound=scaledSlides.back()->pos().x()+scaledSlides.back()->boundingRect().width();
	double slideRightBound2=slides.front()->pos().x()+slides.front()->boundingRect().width();
	double viewRightBound=slidesView->sceneRect().width();
	if(slideRightBound<viewRightBound)
		return false;
	else return true;
}
void snapShotTab::resizeEvent(QResizeEvent *ev)
{
	scene->setSceneRect(sceneView->rect());
	QWidget::resizeEvent(ev);
}
void snapShotTab::setDatabase(Database &db)
{
	this->db=&db;
}
void snapShotTab::addSlide(int id)
{
	db->connect();
	Snapshot snapshot=db->getSnapshot(id);
	db->disconnect();
	QGraphicsSnapShotItem *slide=new QGraphicsSnapShotItem();
	slide->setPixmap(QPixmap().fromImage(snapshot.image));
	slide->setId(id);
	slides.push_back(slide);
	drawSlides(1);
}
void snapShotTab::drawSlides(int n)
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
void snapShotTab::addScenePart(int n)
{
	db->connect();
	QGraphicsPixmapItem *item=new QGraphicsPixmapItem(QPixmap::fromImage(db->getSnapshot(n).image));
	db->disconnect();
	parts.push_back(n);
	scene->addItem(item);
	item->setFlags(QGraphicsItem::ItemIsMovable);
}
void snapShotTab::fixScene()
{
	QPoint min=QPoint(INT_MAX,INT_MAX),max=QPoint(0,0);
	foreach(QGraphicsItem *item,scene->items())
	{
		if(item->scenePos().x()<=min.x() && item->scenePos().y()<=min.y())
			min=item->scenePos().toPoint();
		if((item->scenePos().x()+item->boundingRect().width())>=max.x() && (item->scenePos().y()+item->boundingRect().height())>=max.y())
			max=QPoint(item->scenePos().x()+item->boundingRect().width(),item->scenePos().y()+item->boundingRect().height());
	}
	QPixmap scene=QPixmap();
	scene=scene.grabWidget(sceneView,QRect(min,max));
	db->connect();
	int sceneId=db->addScene(scene);
	foreach(int snapshot_id,parts)
	{
		db->addPart(sceneId,snapshot_id);
	}
	db->disconnect();
	//QLabel *lbl=new QLabel();
	//lbl->setPixmap(scene);
	//lbl->show();
	emit sceneFixed(sceneId);
}
void snapShotTab::clearScene()
{
	scene->clear();
}
void snapShotTab::clearSlidesList()
{
	slides.clear();
	scaledSlides.clear();
	slidesScene->clear();
}
void snapShotTab::clearAll()
{
	clearScene();
	clearSlidesList();
}
snapShotTab::~snapShotTab()
{
	delete scene;
	delete slidesScene;
}
