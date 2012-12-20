#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "views/VideoView.h"
#include "fuzzy/FuzzyGrid.h"
class VideoTab : public QWidget
{
	Q_OBJECT
signals:
    void factorsChanged(int, QSize gridSize, QVector<double>&);
public:
	VideoTab(QWidget *parent = 0, Qt::WFlags flags = 0);
	~VideoTab();
public slots:
    void fixScene();
	void radioToggled(bool checked);
    void renewFactors();
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
