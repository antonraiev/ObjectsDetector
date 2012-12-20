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
    int granulaSize();
    QSize gridSize();
    QVector<double>& fuzzyFactors();
	bool gridVisible();
    bool sceneFixed();
public slots:
	void showGrid(int state);
	void showFactors(int state);
	void doCalculations();
    void fixStaticScene();
private:
	bool isGridVisible;
	bool isFactorsVisible;
    bool isSceneFixed;
    int m_granulaSize;
    QSize gridDimensions;
	QGraphicsScene *scene;
	QVector<QGraphicsRectItem*> granules;
	QVector<QGraphicsTextItem*> factors;
    QVector<double> staticFactors;
    QVector<double> diffFactors;
};
#endif
