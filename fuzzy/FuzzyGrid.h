#include <QtGui>

class FuzzyGrid : public QObject
{
	Q_OBJECT
public:
	FuzzyGrid();
	FuzzyGrid(QGraphicsScene *scene, int size = 5);
	void setScene(QGraphicsScene *scene);
	void setGranulaSize(int size);
public slots:
	void showGrid(int state);
	void doCalculations();
private:
	int gridSize;
	QGraphicsScene *scene;
	QList<QGraphicsRectItem*> granules;
};