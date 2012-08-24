#ifndef SCENETAB_H
#define SCENETAB_H
#include <QtGui>
#include "Database.h"
#include "CvSURF.h"
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
	void setDatabase(Database &db);
	void runScenesDialog();
	void findObjects();
	void buildMap();
protected:
	virtual void resizeEvent(QResizeEvent *ev);
private:
	CvSURF surf;
	QGraphicsScene *scene;
	QGraphicsView *sceneView;
	Scene sceneStruct;
	Database *db;
	QGridLayout *mainLayout;
	multimap<bool, QRect> mapPoints;
	double robotHeightPx;
	double robotHeightSm;
};

#endif // SCENETAB_H
