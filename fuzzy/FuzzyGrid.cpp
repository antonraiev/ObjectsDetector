#include "FuzzyGrid.h"
#include <iostream>

FuzzyGrid::FuzzyGrid()
{

}

void FuzzyGrid::setScene(QGraphicsScene *scene)
{
	this->scene = scene;
}

FuzzyGrid::FuzzyGrid(QGraphicsScene *scene, int size)
{
	setScene(scene);
	setGranulaSize(size);
}

void FuzzyGrid::setGranulaSize(int size)
{
	granules.clear();
	gridSize = size;
	for(int i = 0; i < scene->width(); i += gridSize)
	{
		for(int j = 0; j < scene->height(); j += gridSize)
		{
			QGraphicsRectItem *granula = new QGraphicsRectItem();
			granula->setRect(i, j, gridSize, gridSize);
			granules.push_back(granula);
		}
	}
}

void FuzzyGrid::showGrid(int state)
{
	if(state == Qt::Checked)
	{
		foreach(QGraphicsRectItem *granula, granules)
		{
			scene->addItem(granula);
		}
	}
	else
	{
		foreach(QGraphicsRectItem *granula, granules)
		{
			scene->removeItem(granula);
		}
	}
}

void FuzzyGrid::doCalculations()
{
	showGrid(Qt::Unchecked);
	QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);  
	image.fill(Qt::transparent);                                              

	QPainter painter(&image);
	scene->render(&painter);

	foreach(QGraphicsRectItem *granula, granules)
	{
		QRectF granulaRect = granula->rect();
		int pixelsCount = 0;
		for(int i = granulaRect.x(); i < granulaRect.x() + granulaRect.width(); i++)
		{
			for(int j = granulaRect.y(); j < granulaRect.y() + granulaRect.height(); j++)
			{
				if(image.pixel(i, j) == qRgb(0, 255, 0) || image.pixel(i, j) == qRgb(255, 0, 0))
				{
					pixelsCount++;
				}
			}
		}

		QFont font("Times", 1);
		font.setLetterSpacing(QFont::PercentageSpacing, 50);
		double factor = -1 + 2 * (pixelsCount / double((granulaRect.width() * granulaRect.height())));
		QGraphicsTextItem *text = scene->addText(QString().number(factor), font);
		text->setPos(granulaRect.x() - 2, granulaRect.y() - 3);
	}
	showGrid(Qt::Checked);
}