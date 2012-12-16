#ifndef SNAPSHOTWIDGET_H
#define SNAPSHOTWIDGET_H

#include <QtGui>
#include <vector>
#include "../database/Database.h"
#include "../views/SlidesView.h"
class QGraphicsSnapShotItem;
#define SlidesList std::vector<QGraphicsSnapShotItem*>
class SnapshotTab : public QWidget
{
	Q_OBJECT
signals:
	void sceneFixed(int id);
public:
	SnapshotTab(QWidget *parent = 0);
	void addSlide(int id);
	~SnapshotTab();
public slots:
	void addSlideFromCamera(int id);
	void addScene(int id);
	void drawSlides(int n);
	void moveSlidesRight();
	void moveSlidesLeft();
	void runSnapshotsDialog();
    void addScenePart(int n);
	void runScenesDialog();
	void resizeSceneBounds();
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
};

#endif // SNAPSHOTWIDGET_H
