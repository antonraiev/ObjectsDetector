#ifndef SLIDESVIEW_H
#define SLIDESVIEW_H

#include <QtGui>

class SlidesView : public QGraphicsView
{
public:
	SlidesView(QWidget *parent=0);
protected:
	virtual void resizeEvent(QResizeEvent *ev);
private:
	bool first_shown;
};

#endif // SLIDESVIEW_H
