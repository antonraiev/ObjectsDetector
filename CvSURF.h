#pragma once
#include <cv.h>
#include <highgui.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <QtGui>
using namespace std;
class CvSURF
{
public:
	CvSURF(void);
	int compare(QPixmap *scene,QPixmap *object,QPoint *outputCoords);
	IplImage* CvSURF::QImageToIplImage(QPixmap * qPix);
	QImage IplCopyToQImage(IplImage *img);
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

