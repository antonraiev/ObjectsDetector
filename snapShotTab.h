#ifndef SNAPSHOTWIDGET_H
#define SNAPSHOTWIDGET_H

#include <QtGui>
#include <vector>
#include "Database.h"
#include "SlidesView.h"
class QGraphicsSnapShotItem;
#define SlidesList std::vector<QGraphicsSnapShotItem*>
class snapShotTab : public QWidget
{
	Q_OBJECT
signals:
	void sceneFixed(int id);
public:
	snapShotTab(QWidget *parent = 0);
	~snapShotTab();
	void setDatabase(Database &db);
public slots:
	void addSlide(int id);
	void drawSlides(int n);
	void moveSlidesRight();
	void moveSlidesLeft();
	void runSnapshotsDialog();
    void addScenePart(int n);
	void fixScene();
	void clearScene();
	void clearSlidesList();
	void clearAll();
protected:
	bool canShiftedRight();
	bool canShiftedLeft();
	virtual void resizeEvent(QResizeEvent *ev);
private:
	QGraphicsScene *slidesScene;
	SlidesView *slidesView;
	SlidesList slides;
	SlidesList scaledSlides;
	QList<int> parts;
	int slideShift;
	QPushButton *leftArrow,*rightArrow;
	QGraphicsScene *scene;
	QGraphicsView *sceneView;
	Database *db;
};

#endif // SNAPSHOTWIDGET_H
