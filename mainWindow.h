#ifndef OBSTACLEDETECTOR_H
#define OBSTACLEDETECTOR_H

#include <QtGui>
#include "videoTab.h"
#include "snapShotTab.h"
#include "SceneTab.h"
#include "DbTab.h"
#include "Database.h"
class mainWindow : public QWidget
{
	Q_OBJECT
public:
	mainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~mainWindow();

private:
	videoTab *vTab;
	snapShotTab *snapTab;
	SceneTab *sceneTab;
	DbTab *dbTab;
	Database db;
};

#endif // OBSTACLEDETECTOR_H
