#ifndef OBJECTVIEW_H
#define OBJECTVIEW_H

#include <QtGui>

class ObjectView : public QGraphicsView
{
	Q_OBJECT

public:
	ObjectView(QWidget *parent=0);
	QRect selectedArea();
	~ObjectView();
protected:
	virtual void mousePressEvent(QMouseEvent *ev);
	virtual void mouseReleaseEvent(QMouseEvent *ev);
	virtual void mouseMoveEvent(QMouseEvent *ev);
	virtual void paintEvent(QPaintEvent *ev);
private:
	bool mouseDown;
	QPoint topLeft;
	QPoint bottomRight;
};

#endif // OBJECTVIEW_H
