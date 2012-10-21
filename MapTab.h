#ifndef MAPTAB_H
#define MAPTAB_H
#include <QtGui>
#include "Database.h"
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
	void setDatabase(Database &db);
	void runMapsDialog();
	void saveMapToFile();
	void sendToKate();
	void connectedToKate();
	void errorToKate(QAbstractSocket::SocketError error);
protected:
	virtual void resizeEvent(QResizeEvent *ev);
private:
	QGraphicsScene *scene;
	QGraphicsView *sceneView;
	Map currentMap;
	Database *db;
	QGridLayout *mainLayout;
	QTcpSocket *kateSocket;
};

#endif // MAPTAB_H
