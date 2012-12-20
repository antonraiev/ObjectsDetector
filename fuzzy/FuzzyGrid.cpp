#include "FuzzyGrid.h"
#include <iostream>
#include <algorithm>

FuzzyGrid::FuzzyGrid()
{
    isGridVisible = isFactorsVisible = isSceneFixed = false;
}

FuzzyGrid::FuzzyGrid(QGraphicsScene *scene, int size)
{
    setScene(scene);
    isGridVisible = isFactorsVisible = isSceneFixed = false;
    setGranulaSize(size);
}

void FuzzyGrid::setScene(QGraphicsScene *scene)
{
    this->scene = scene;
}

void FuzzyGrid::fixStaticScene()
{
    staticFactors.clear();
    diffFactors.clear();
    foreach(QGraphicsTextItem *factor, factors)
    {
        staticFactors.push_back(factor->toPlainText().toDouble());
        diffFactors.push_back(0);
        isSceneFixed = true;
    }
}

void FuzzyGrid::setGranulaSize(int size)
{
    isSceneFixed = false;
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
    m_granulaSize = size * 20;  // magic coefficient
    QFont font("Arial", m_granulaSize / 5);

    for(int i = 0; i < scene->width(); i += m_granulaSize)
	{
        for(int j = 0; j < scene->height(); j += m_granulaSize)
		{
			QGraphicsRectItem *granula = new QGraphicsRectItem();
            granula->setRect(i, j, m_granulaSize, m_granulaSize);
			granules.push_back(granula);
			
			QGraphicsTextItem *factor = new QGraphicsTextItem("0");
			factor->setFont(font);
			factor->setPos(i, j);
			factors.push_back(factor);
		}
	}

    gridDimensions = QSize(scene->width() / m_granulaSize, scene->height() / m_granulaSize);

	if(gridRestore)
	{
		showGrid(Qt::Checked);
	}
	if(factorsRestore)
	{
		showFactors(Qt::Checked);
    }
}

int FuzzyGrid::granulaSize()
{
    return m_granulaSize;
}

QSize FuzzyGrid::gridSize()
{
    return gridDimensions;
}

QVector<double> &FuzzyGrid::fuzzyFactors()
{
    return diffFactors;
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

bool FuzzyGrid::sceneFixed()
{
    return isSceneFixed;
}

void FuzzyGrid::doCalculations()
{
    bool restore = false;
    if(gridVisible())
    {
        showGrid(Qt::Unchecked);
        restore = true;
    }
	QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);  
	image.fill(Qt::transparent);                                              

	QPainter painter(&image);
	scene->render(&painter);
    if(restore)
    {
        showGrid(Qt::Checked);
    }

    double whiteBrightness = 255 * m_granulaSize * m_granulaSize;
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
			}
		}

		double factor = -1 + 2 * (brightness / whiteBrightness);
        if(isSceneFixed)
        {
            diffFactors[factorIndex] = fabs(factor - staticFactors[factorIndex]);
//            factors[factorIndex]->setPlainText(QString().number(-1 + fabs(factor-staticFactors[factorIndex]), 'g', 2));
        }
        else
        {
            factors[factorIndex]->setPlainText(QString().number(factor, 'g', 2));
        }
		factorIndex++;
	}
    if(isSceneFixed)
    {
        factorIndex = 0;
        double maxValue = *std::max_element(diffFactors.begin(), diffFactors.end());
        foreach(QGraphicsRectItem *granula, granules)
        {
            if(diffFactors[factorIndex] > 0.2)
            {
                factors[factorIndex]->setPlainText(QString().number(-1 + diffFactors[factorIndex] * 2 / maxValue, 'g', 2));
            }
            else
            {
                factors[factorIndex]->setPlainText(QString().number(-1 + diffFactors[factorIndex], 'g', 2));
            }
            factorIndex++;
        }
    }
}
/*
 * 0.8 => 2
 * 0.2 => 0.5
 */
