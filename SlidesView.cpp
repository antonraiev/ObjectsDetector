#include "SlidesView.h"

SlidesView::SlidesView(QWidget *parent)
	: QGraphicsView(parent)
{
	first_shown=true;
}

void SlidesView::resizeEvent(QResizeEvent *ev)
{
	QGraphicsView::resizeEvent(ev);

    if (!first_shown)
    {
        centerOn(0, 0);
        first_shown = true;
    }
    QPointF topleft = mapToScene(viewport()->rect().topLeft());
    resetMatrix();
    QPointF shift = (mapToScene(viewport()->rect().bottomRight() + QPoint(1, 1)) - mapToScene(viewport()->rect().topLeft()));
    shift /= (double) ev->size().width() / scene()->width();

    fitInView(QRectF(topleft, topleft + shift));
}