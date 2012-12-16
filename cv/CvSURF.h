#pragma once
#include <cv.h>
//#include <opencv2/objdetect/objdetect.hpp>
//#include <opencv2/features2d/features2d.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
//#include <opencv2/imgproc/imgproc_c.h>
//#include <opencv2/legacy/legacy.hpp>
//#include <opencv2/legacy/compat.hpp>
#include <highgui.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <QtGui>
#include "QtOpenCV.h"
using namespace std;
class CvSURF
{
public:
	CvSURF(void);
	int compare(QPixmap *scene,QPixmap *object,QPoint *outputCoords);
    static IplImage* QImageToIplImage(QPixmap * qPix);
	static QImage IplCopyToQImage(IplImage *img);
	~CvSURF(void);
protected:
	double compareSURFDescriptors(const float* d1, const float* d2, double best, int length);
	int naiveNearestNeighbor(const float* vec, int laplacian,
           const CvSeq* model_keypoints,
           const CvSeq* model_descriptors);
	void findPairs(const CvSeq* objectKeypoints, const CvSeq* objectDescriptors,
           const CvSeq* imageKeypoints, const CvSeq* imageDescriptors, vector<int>& ptpairs);
	int locatePlanarObject( const CvSeq* objectKeypoints, const CvSeq* objectDescriptors,
           const CvSeq* imageKeypoints, const CvSeq* imageDescriptors,
           const CvPoint src_corners[4], CvPoint dst_corners[4]);
};

