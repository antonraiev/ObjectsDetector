#ifndef MAPTAB_H
#define MAPTAB_H
#include <QtGui>
#include "fuzzy/FuzzyGrid.h"
#include <qabstractsocket.h>
#include <qtcpsocket.h>

class MapTab : public QWidget
{
	Q_OBJECT
public:
	MapTab(QWidget *parent=0);
	~MapTab();
public slots:
    void renewMap(int size, QSize gridSize, QVector<double>& factors);
	void saveMapToFile();
	void sendToKate();
	void connectedToKate();
    void errorFromKate(QAbstractSocket::SocketError error);
protected:
	virtual void resizeEvent(QResizeEvent *ev);
	virtual void wheelEvent(QWheelEvent *ev);
	virtual void keyPressEvent(QKeyEvent *ev);
private:
    QLineEdit *ipEdit;
    QLineEdit *portEdit;
    QTextEdit *networkLog;
    QPushButton *sendButton;
	QGraphicsScene *scene;
	QGraphicsView *sceneView;
	QGridLayout *mainLayout;
	QTcpSocket *kateSocket;
};

#endif // MAPTAB_H
