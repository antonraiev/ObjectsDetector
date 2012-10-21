#include "QGraphicsSnapShotItem.h"
#include <QtSql>
QGraphicsSnapShotItem::QGraphicsSnapShotItem(QGraphicsItem *parent,QGraphicsScene *scene)
	: QGraphicsPixmapItem(parent,scene)
{
	setAcceptHoverEvents(true);
	paintBorder=false;
}
QGraphicsSnapShotItem::QGraphicsSnapShotItem(QPixmap pixmap,QGraphicsScene *scene)
	: QGraphicsPixmapItem(pixmap,0,scene)
{
	setAcceptHoverEvents(true);
	paintBorder=false;
}
QRectF QGraphicsSnapShotItem::boundingRect() const
{
	QRectF r=QGraphicsPixmapItem::boundingRect();
//	return QRect(r.top()-15,r.left()-15,r.width()+30,r.height()+30);
	return r;
}
void QGraphicsSnapShotItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
	QGraphicsPixmapItem::paint(painter,option,widget);
	if(paintBorder)
	{
		painter->save();
		painter->setPen(QPen(QBrush(Qt::red),3));
		painter->drawRect(this->boundingRect());
		painter->restore();
	}
}
void QGraphicsSnapShotItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *ev)
{
	emit doubleClicked(dbId);
	QGraphicsPixmapItem::mouseDoubleClickEvent(ev);
//	QGraphicsPixmapItem::hoverEnterEvent(
}
void QGraphicsSnapShotItem::hoverEnterEvent(QGraphicsSceneHoverEvent *ev)
{
	paintBorder=true;
	QGraphicsPixmapItem::hoverEnterEvent(ev);
}
void QGraphicsSnapShotItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *ev)
{
	paintBorder=false;
	QGraphicsPixmapItem::hoverLeaveEvent(ev);
}
void QGraphicsSnapShotItem::mouseMoveEvent(QGraphicsSceneMouseEvent *ev)
{
	QList<QGraphicsItem*> items=this->scene()->items();
	foreach(QGraphicsItem *item,items)
	{
		if(item!=this && this->collidesWithItem(item,Qt::IntersectsItemBoundingRect))
		{
//			this->setOpacity(0.5);
		}
		else
		{
//			this->setOpacity(1);
		}
	}
	QGraphicsPixmapItem::mouseMoveEvent(ev);
}
void QGraphicsSnapShotItem::setId(int id)
{
	dbId=id;
}
int QGraphicsSnapShotItem::id()
{
	return dbId;
}