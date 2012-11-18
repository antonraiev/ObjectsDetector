#ifndef OBSTACLEDETECTOR_H
#define OBSTACLEDETECTOR_H

#include <QtGui>
#include "../tabs/VideoTab.h"
#include "../tabs/SnapshotTab.h"
#include "../tabs/SceneTab.h"
#include "../tabs/MapTab.h"
#include "../tabs/DbTab.h"
#include "../database/Database.h"
class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();

private:
	VideoTab *vTab;
	SnapshotTab *snapTab;
	SceneTab *sceneTab;
	MapTab *mapTab;
	DbTab *dbTab;
};

#endif // OBSTACLEDETECTOR_H
