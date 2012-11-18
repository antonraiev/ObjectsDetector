#ifndef MAPTAB_H
#define MAPTAB_H
#include <QtGui>
#include "../database/Database.h"
#include "../fuzzy/FuzzyGrid.h"
#include <qabstractsocket.h>
#include <qtcpsocket.h>

class MapTab : public QWidget
{
	Q_OBJECT
public:
	MapTab(QWidget *parent=0);
	~MapTab();
public slots:
	void addMap(int id);
	void runMapsDialog();
	void saveMapToFile();
	void sendToKate();
	void connectedToKate();
	void errorToKate(QAbstractSocket::SocketError error);
protected:
	virtual void resizeEvent(QResizeEvent *ev);
	virtual void wheelEvent(QWheelEvent *ev);
	virtual void keyPressEvent(QKeyEvent *ev);
private:
	QGraphicsScene *scene;
	QGraphicsView *sceneView;
	Map currentMap;
	FuzzyGrid *fuzzyGrid;
	QGridLayout *mainLayout;
	QTcpSocket *kateSocket;
};

#endif // MAPTAB_H
