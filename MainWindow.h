#ifndef OBSTACLEDETECTOR_H
#define OBSTACLEDETECTOR_H

#include <QtGui>
#include "tabs/VideoTab.h"
#include "tabs/MapTab.h"

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();

private:
	VideoTab *vTab;
	MapTab *mapTab;
};

#endif // OBSTACLEDETECTOR_H
