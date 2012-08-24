#ifndef MAPTAB_H
#define MAPTAB_H
#include <QtGui>
#include "Database.h"
class MapTab : public QWidget
{
	Q_OBJECT
public:
	MapTab(QWidget *parent=0);
	~MapTab();
public slots:
	void addMap(int id);
	void setDatabase(Database &db);
	void runMapsDialog();
	void saveMap();
protected:
	virtual void resizeEvent(QResizeEvent *ev);
private:
	QGraphicsScene *scene;
	QGraphicsView *sceneView;
	Map currentMap;
	Database *db;
	QGridLayout *mainLayout;
};

#endif // MAPTAB_H
