#include "FuzzyGrid.h"
#include <iostream>

FuzzyGrid::FuzzyGrid()
{
	isGridVisible = isFactorsVisible = false;
}

void FuzzyGrid::setScene(QGraphicsScene *scene)
{
	this->scene = scene;
}

FuzzyGrid::FuzzyGrid(QGraphicsScene *scene, int size)
{
	setScene(scene);
	isGridVisible = isFactorsVisible = false;
	setGranulaSize(size);
}

void FuzzyGrid::setGranulaSize(int size)
{
	bool gridRestore = false, factorsRestore = false;
	if(isGridVisible)
	{
		showGrid(Qt::Unchecked);
		gridRestore = true;
	}
	if(isFactorsVisible)
	{
		showFactors(Qt::Unchecked);
		factorsRestore = true;
	}

	granules.clear();
	factors.clear();
	gridSize = size * 20;  // magic coefficient
	QFont font("Times", gridSize / 5);
	font.setLetterSpacing(QFont::PercentageSpacing, 50);

	for(int i = 0; i < scene->width(); i += gridSize)
	{
		for(int j = 0; j < scene->height(); j += gridSize)
		{
			QGraphicsRectItem *granula = new QGraphicsRectItem();
			granula->setRect(i, j, gridSize, gridSize);
			granules.push_back(granula);
			
			QGraphicsTextItem *factor = new QGraphicsTextItem("0");
			factor->setFont(font);
			factor->setPos(i, j);
			factors.push_back(factor);
		}
	}

	if(gridRestore)
	{
		showGrid(Qt::Checked);
	}
	if(factorsRestore)
	{
		showFactors(Qt::Checked);
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
		isGridVisible = true;
	}
	else
	{
		foreach(QGraphicsRectItem *granula, granules)
		{
			scene->removeItem(granula);
		}
		isGridVisible = false;
	}
}

void FuzzyGrid::showFactors(int state)
{
	if(state == Qt::Checked)
	{
		foreach(QGraphicsTextItem *factor, factors)
		{
			scene->addItem(factor);
		}
		isFactorsVisible = true;
	}
	else
	{
		foreach(QGraphicsTextItem *factor, factors)
		{
			scene->removeItem(factor);
		}
		isFactorsVisible = false;
	}
}

bool FuzzyGrid::gridVisible()
{
	return isGridVisible;
}

void FuzzyGrid::doCalculations()
{
//	showFactors(Qt::Unchecked);
	QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);  
	image.fill(Qt::transparent);                                              

	QPainter painter(&image);
	scene->render(&painter);

	QRgb whitePixel = qRgb(255, 255, 255);
	double whiteBrightness = 255 * gridSize * gridSize;
	int factorIndex = 0;
	foreach(QGraphicsRectItem *granula, granules)
	{
		QRectF granulaRect = granula->rect();
		double brightness = 0;
		int xGranulaCoord = granulaRect.x(), granulaWidth = granulaRect.x() + granulaRect.width();
		for(int i = xGranulaCoord; i < granulaWidth; i++)
		{
			int yGranulaCoord = granulaRect.y(), granulaHeight = granulaRect.y() + granulaRect.height();
			for(int j = yGranulaCoord; j < granulaHeight; j++)
			{
				QRgb pixelRgb = image.pixel(i, j);
				brightness += (0.2126*qRed(pixelRgb)) + (0.7152*qGreen(pixelRgb)) + (0.0722*qBlue(pixelRgb));
//				whiteBrightness += (0.2126*qRed(whitePixel)) + (0.7152*qGreen(whitePixel)) + (0.0722*qBlue(whitePixel));
			}
		}

//		QFont font("Times", gridSize / 5);
//		font.setLetterSpacing(QFont::PercentageSpacing, 50);
		double factor = -1 + 2 * (brightness / whiteBrightness);
		factors[factorIndex]->setPlainText(QString().number(factor));
		factorIndex++;
//		QGraphicsTextItem *text = new QGraphicsTextItem(QString().number(factor));
//		text->setFont(font);
//		text->setPos(granulaRect.x(), granulaRect.y());
//		factors.push_back(text);
	}
//	showFactors(Qt::Checked);
}