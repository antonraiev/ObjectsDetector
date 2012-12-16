#ifndef FUZZYGRID_H
#define FUZZYGRID_H

#include <QtGui>

class FuzzyGrid : public QObject
{
	Q_OBJECT
public:
	FuzzyGrid();
	FuzzyGrid(QGraphicsScene *scene, int size = 1);
	void setScene(QGraphicsScene *scene);
	void setGranulaSize(int size);
	bool gridVisible();
public slots:
	void showGrid(int state);
	void showFactors(int state);
	void doCalculations();
private:
	bool isGridVisible;
	bool isFactorsVisible;
	int gridSize;
	QGraphicsScene *scene;
	QVector<QGraphicsRectItem*> granules;
	QVector<QGraphicsTextItem*> factors;
};
#endif