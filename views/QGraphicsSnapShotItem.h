#ifndef QGRAPHICSSNAPSHOTITEM_H
#define QGRAPHICSSNAPSHOTITEM_H

#include <QtGui>

class QGraphicsSnapShotItem : public QObject,public QGraphicsPixmapItem
{
	Q_OBJECT
signals:
	void doubleClicked(int n);
public:
	QGraphicsSnapShotItem(QGraphicsItem *parent=0,QGraphicsScene *scene=0);
	QGraphicsSnapShotItem(QPixmap pixmap,QGraphicsScene *scene=&QGraphicsScene());
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *,QWidget *);
	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *ev);
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *ev);
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *ev);
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *ev);
	void setId(int id);
	int id();
private:
	bool paintBorder;
	int dbId;
};

#endif // QGRAPHICSSNAPSHOTITEM_H
