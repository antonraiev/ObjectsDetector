#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/calib3d/calib3d.hpp> // for homography
#include <cv.h>
#include "QtOpenCV.h"
#include <QtGui>
#include <vector>

struct SiftResult
{
	SiftResult(bool status)
	{
		isHomographyFound = status;
	}
	SiftResult(bool status, QGraphicsRectItem *item)
	{
		isHomographyFound = status;
		rectItem = item;
	}
	bool isHomographyFound;
	QGraphicsRectItem *rectItem;
};

class CvSIFT
{
public:
	CvSIFT();
	~CvSIFT();
	void setScene(const QImage &scene);
	SiftResult doSIFT(/*const QImage &scene, */const QImage &object);
private:
	std::vector<cv::KeyPoint> sceneKeypoints;
	cv::Mat sceneDescriptors;
	cv::SiftFeatureDetector detector;
	cv::DescriptorExtractor *extractor;
};