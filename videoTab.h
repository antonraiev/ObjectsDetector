#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "MeasureUnit.h"
#include "VideoSource.h"
#include "Controller.h"
#include "CMControl.h"
#include "camera.h"
#include "videoWidget.h"
#include "Database.h"
class videoTab : public QWidget
{
	Q_OBJECT
signals:
	void snapshotAdded(int id);
public:
	videoTab(QWidget *parent = 0, Qt::WFlags flags = 0);
	~videoTab();
	void setDatabase(Database &db);
public slots:
	void takeSnapshot();
	void upCameraMove();
	void downCameraMove();
	void leftCameraMove();
	void rightCameraMove();
	void endCameraMove();
protected:
	virtual void paintEvent(QPaintEvent *ev);
private:
	videoWidget *video;
	Database *db;
};

#endif // MAINWINDOW_H
