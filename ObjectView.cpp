#include "ObjectView.h"

ObjectView::ObjectView(QWidget *parent)
	: QGraphicsView(parent)
{
	mouseDown=false;
	setToolTip("Выделите нужный объект мышью");
}
void ObjectView::mousePressEvent(QMouseEvent *ev)
{
	topLeft=ev->pos();
	mouseDown=true;
	QGraphicsView::mousePressEvent(ev);
}
void ObjectView::paintEvent(QPaintEvent *ev)
{
	QGraphicsView::paintEvent(ev);
	if(mouseDown)
	{
		QPen pen=QPen(Qt::red);
		pen.setWidth(3);
		QPainter painter(viewport());
		painter.setPen(pen);
		painter.drawRect(QRect(topLeft,bottomRight));
	}
}
void ObjectView::mouseMoveEvent(QMouseEvent *ev)
{
	if(mouseDown)
	{
		bottomRight=ev->pos();
		viewport()->repaint();
	}
	QGraphicsView::mouseMoveEvent(ev);
}
void ObjectView::mouseReleaseEvent(QMouseEvent *ev)
{
	mouseDown=false;
	QGraphicsView::mouseReleaseEvent(ev);
}
QRect ObjectView::selectedArea()
{
	return QRect(topLeft,bottomRight);
}
ObjectView::~ObjectView()
{

}
