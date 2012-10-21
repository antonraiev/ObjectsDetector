#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "CMControl.h"
#include "../views/VideoView.h"
#include "../database/Database.h"
class VideoTab : public QWidget
{
	Q_OBJECT
signals:
	void snapshotAdded(int id);
public:
	VideoTab(QWidget *parent = 0, Qt::WFlags flags = 0);
	~VideoTab();
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
	VideoView *video;
	Database *db;
};

#endif // MAINWINDOW_H
