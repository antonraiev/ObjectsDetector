#ifndef SCENETAB_H
#define SCENETAB_H
#include <QtGui>
#include "../database/Database.h"
#include "../cv/CvSURF.h"
#include "../cv/CvSIFT.h"
class SceneTab : public QWidget
{
	Q_OBJECT
signals:
	void mapCreated(int id);
public:
	SceneTab(QWidget *parent=0);
	~SceneTab();
public slots:
	void addScene(int id);
	void runScenesDialog();
	void findObjects();
	void buildMap();
protected:
	virtual void resizeEvent(QResizeEvent *ev);
private:
	CvSURF surf;
	CvSIFT sift;
	QGraphicsScene *scene;
	QGraphicsView *sceneView;
	Scene currentScene;
	QGridLayout *mainLayout;
	multimap<bool, QRect> mapPoints;
	double robotHeightPx;
	double robotHeightSm;
};

#endif // SCENETAB_H
