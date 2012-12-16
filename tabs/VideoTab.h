#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "CMControl.h"
#include "../views/VideoView.h"
#include "../database/Database.h"
#include "../fuzzy/FuzzyGrid.h"
class VideoTab : public QWidget
{
	Q_OBJECT
signals:
	void snapshotAdded(int id);
public:
	VideoTab(QWidget *parent = 0, Qt::WFlags flags = 0);
	~VideoTab();
public slots:
	void takeSnapshot();
	void upCameraMove();
	void downCameraMove();
	void leftCameraMove();
	void rightCameraMove();
	void endCameraMove();
	void radioToggled(bool checked);
protected:
	virtual void paintEvent(QPaintEvent *ev);
	virtual	void keyPressEvent(QKeyEvent *ev);
private:
	void createFuzzyControls();
private:
	QGridLayout *mainLayout;
	FuzzyGrid *fuzzyGrid;
	VideoView *video;
	QGraphicsScene *videoScene;
	QGraphicsView *videoView;
};

#endif // MAINWINDOW_H
