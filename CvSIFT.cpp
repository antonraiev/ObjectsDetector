#include "CvSIFT.h"


CvSIFT:: CvSIFT()
{
	cv::initModule_nonfree();
	extractor = new cv::SIFT();
}

CvSIFT::~CvSIFT()
{
	delete extractor;
}

void CvSIFT::setScene(const QImage &scene)
{
	cv::Mat sceneImgc = cvtQImage2CvMat(scene);
	cv::Mat sceneImg;
	cvtColor(sceneImgc, sceneImg, CV_RGB2GRAY);
	if(!sceneImg.empty())
	{
		sceneKeypoints.clear();
		detector.detect(sceneImg, sceneKeypoints);
		extractor->compute(sceneImg, sceneKeypoints, sceneDescriptors);
	}
}
SiftResult CvSIFT::doSIFT(/*const QImage &scene, */const QImage &object)
{
	cv::Mat objectImgc = cvtQImage2CvMat(object);
//	cv::Mat sceneImgc = cvtQImage2CvMat(scene);
	cv::Mat /*sceneImg,*/ objectImg;
	cvtColor(objectImgc, objectImg, CV_RGB2GRAY);
//	cvtColor(sceneImgc, sceneImg, CV_RGB2GRAY);
	if(!objectImg.empty() /*&& !sceneImg.empty()*/)
	{
		std::vector<cv::KeyPoint> objectKeypoints;
//		std::vector<cv::KeyPoint> sceneKeypoints;
		cv::Mat objectDescriptors;
//		cv::Mat sceneDescriptors;
//		cv::SiftFeatureDetector detector;
		detector.detect(objectImg, objectKeypoints);
		int size = (int)objectKeypoints.size();
//		detector.detect(sceneImg, sceneKeypoints);

//		cv::DescriptorExtractor *extractor = new cv::SIFT();
		extractor->compute(objectImg, objectKeypoints, objectDescriptors);
//		extractor->compute(sceneImg, sceneKeypoints, sceneDescriptors);

		cv::Mat results;
		cv::Mat dists;
		int k = 2; // find the 2 nearest neighbors
		if(objectDescriptors.type()==CV_8U)
		{
			// Binary descriptors detected (from ORB or Brief)

			// Create Flann LSH index
			cv::flann::Index flannIndex(sceneDescriptors, cv::flann::LshIndexParams(20, 10, 2));
			results = cv::Mat(objectDescriptors.rows, k, CV_32SC1); // Results index
			dists = cv::Mat(objectDescriptors.rows, k, CV_32FC1); // Distance results are CV_32FC1 ?!?!? NOTE OpenCV doc is not clear about that...

			// search (nearest neighbor)
			flannIndex.knnSearch(objectDescriptors, results, dists, k, cv::flann::SearchParams() );
		}
		else
		{
			// assume it is CV_32F

			// Create Flann KDTree index
			cv::flann::Index flannIndex(sceneDescriptors, cv::flann::KDTreeIndexParams());
			results = cv::Mat(objectDescriptors.rows, k, CV_32SC1); // Results index
			dists = cv::Mat(objectDescriptors.rows, k, CV_32FC1); // Distance results are CV_32FC1

			// search (nearest neighbor)
			flannIndex.knnSearch(objectDescriptors, results, dists, k, cv::flann::SearchParams() );
		}

		// Find correspondences by NNDR (Nearest Neighbor Distance Ratio)
		float nndrRatio = 0.6;
		std::vector<cv::Point2f> mpts_1, mpts_2; // Used for homography
		std::vector<int> indexes_1, indexes_2; // Used for homography
		std::vector<uchar> outlier_mask;  // Used for homography
		for(int i=0; i<objectDescriptors.rows; ++i)
		{
			// Check if this descriptor matches with those of the objects
			// Apply NNDR
			if(dists.at<float>(i,0) <= nndrRatio * dists.at<float>(i,1))
			{
				mpts_1.push_back(objectKeypoints.at(i).pt);
				indexes_1.push_back(i);

				mpts_2.push_back(sceneKeypoints.at(results.at<int>(i,0)).pt);
				indexes_2.push_back(results.at<int>(i,0));
			}
		}

		// FIND HOMOGRAPHY
		unsigned int minInliers = 8;
		if(mpts_1.size() >= minInliers)
		{
			cv::Mat H = findHomography(mpts_1,
					mpts_2,
					cv::RANSAC,
					1.0,
					outlier_mask);
			int inliers=0, outliers=0;
			for(unsigned int k=0; k<mpts_1.size();++k)
			{
				if(outlier_mask.at(k))
				{
					++inliers;
				}
				else
				{
					++outliers;
				}
			}
			QTransform hTransform(
			H.at<double>(0,0), H.at<double>(1,0), H.at<double>(2,0),
			H.at<double>(0,1), H.at<double>(1,1), H.at<double>(2,1),
			H.at<double>(0,2), H.at<double>(1,2), H.at<double>(2,2));
			QRectF orect = QPixmap::fromImage(cvtCvMat2QImage(objectImg)).rect();
			QGraphicsRectItem *rectItem = new QGraphicsRectItem(QPixmap::fromImage(cvtCvMat2QImage(objectImg)).rect());
			rectItem->setTransform(hTransform);
			orect = rectItem->rect();
			return SiftResult(true, rectItem);
		}
		return SiftResult(false);
	}
	return SiftResult(false);
}