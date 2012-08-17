#include "CvSURF.h"


CvSURF::CvSURF(void)
{
}
int CvSURF::compare(QPixmap *scene,QPixmap *object,QPoint *outputCoords)
{
	IplImage *cvScene=QImageToIplImage(scene);
	IplImage *cvObject=QImageToIplImage(object);

	IplImage *destImage=0;
    IplImage* object_color = cvCreateImage(cvGetSize(cvObject),8,3);
    cvCvtColor(cvObject,object_color,CV_GRAY2BGR);
    CvSeq *objectKeypoints = 0, *objectDescriptors = 0;
    CvSeq *imageKeypoints = 0, *imageDescriptors = 0;
    int i;
    // ������������� ��������� CvSURFParams � �������� ������������ � 128
    // ���������
    CvSURFParams params = cvSURFParams(500, 1);
    CvMemStorage* storage = cvCreateMemStorage(0);
    cvExtractSURF(cvObject,0,&objectKeypoints,&objectDescriptors,storage,params );
    // ���� ����������� �����
    cvExtractSURF(cvScene,0, &imageKeypoints, &imageDescriptors, storage, params );
    CvPoint src_corners[4] = {{0,0}, {cvObject->width,0}, {cvObject->width, cvObject->height}, {0, cvObject->height}};
    CvPoint dst_corners[4];
    IplImage* correspond = cvCreateImage(cvGetSize(cvScene), 8, 1 );
    cvCopy( cvScene, correspond );
    static CvScalar colors[] =
    {
        {{0,0,255}},
        {{0,128,255}},
        {{0,255,255}},
        {{0,255,0}},
        {{255,128,0}},
        {{255,255,0}},
        {{255,0,0}},
        {{255,0,255}},
        {{255,255,255}}
    };
    // �������� �������, ��������� ������ �� ������
    if(locatePlanarObject(objectKeypoints, objectDescriptors,imageKeypoints,
        imageDescriptors,src_corners,dst_corners))
    {
         // �������� ������ ��������������
        for( i = 0; i < 4; i++ )
        {
            CvPoint r1 = dst_corners[i%4];
			outputCoords[i]=QPoint(r1.x,r1.y);
        }
		return 0;
    }
	else return -1;
}
// ��������� ���� ������������
double CvSURF::compareSURFDescriptors( const float* d1, const float* d2, double best, int length )
{
    double total_cost = 0;
    assert( length % 4 == 0 );
    for( int i = 0; i < length; i += 4 )
    {
        double t0 = d1[i] - d2[i];
        double t1 = d1[i+1] - d2[i+1];
        double t2 = d1[i+2] - d2[i+2];
        double t3 = d1[i+3] - d2[i+3];
        total_cost += t0*t0 + t1*t1 + t2*t2 + t3*t3;
        if( total_cost > best )
            break;
    }
    return total_cost;
}
QImage CvSURF::IplCopyToQImage(IplImage *iplImg)
{
	int h = iplImg->height;
	int w = iplImg->width;
        QImage img(w, h, QImage::Format_ARGB32);
		int channels=iplImg->nChannels;
        char* data = iplImg->imageData;
    
        for(int y = 0; y < h; (y++, data += iplImg->widthStep))
	{
		for(int x = 0; x < w; x++)
		{
			char r, g, b, a = 0;
			if (channels == 1)
			{
				r = data[x * channels];
				g = data[x * channels];
				b = data[x * channels];
			}
			else if (channels == 3 || channels == 4)
			{
				r = data[x * channels + 2];
				g = data[x * channels + 1];
				b = data[x * channels];
			}
            
			if (channels == 4)
			{
				a = data[x * channels + 3];
				img.setPixel(x, y, qRgba(r, g, b, a));
			}
			else
			{
				img.setPixel(x, y, qRgb(r, g, b));
			}
		}
	}
	return img;
}
IplImage* CvSURF::QImageToIplImage(QPixmap *qPix)
{
	QImage *qImage=&(qPix->toImage());
    int width=qImage->width();
    int height=qImage->height();
    CvSize Size;
    Size.height=height;
    Size.width=width;
    IplImage *charIplImageBuffer=cvCreateImage(Size,IPL_DEPTH_8U,1);
    for(int y=0;y<height;y++)
    {
        for(int x=0;x<width;x++ )
        {
            QRgb color = qImage->pixel(x,y);
            cvSet2D(charIplImageBuffer,y,x,cvScalar(qGray(color),qGray(color),qGray(color),1));
        }
	}
    return charIplImageBuffer;
}
// ���������� ���� ����������� ������� �� ����� ������������� �����
int CvSURF::naiveNearestNeighbor( const float* vec, int laplacian,
                      const CvSeq* model_keypoints,
                      const CvSeq* model_descriptors )
{
    int length = (int)(model_descriptors->elem_size/sizeof(float));
    int i, neighbor = -1;
    double d, dist1 = 1e6, dist2 = 1e6;
    CvSeqReader reader, kreader;
    // ��������� ����������� �����
    cvStartReadSeq( model_keypoints, &kreader, 0 );
    cvStartReadSeq( model_descriptors, &reader, 0 );
    // ������� ���� ������������ �����
    for( i = 0; i < model_descriptors->total; i++ )
    {
        const CvSURFPoint* kp = (const CvSURFPoint*)kreader.ptr;
        const float* mvec = (const float*)reader.ptr;
        CV_NEXT_SEQ_ELEM( kreader.seq->elem_size, kreader );
        CV_NEXT_SEQ_ELEM( reader.seq->elem_size, reader );
        // ��� ��������� ������� ������������ ��������� ������������
        if( laplacian != kp->laplacian )
            continue;
        // ��������� ������������
        d = compareSURFDescriptors( vec, mvec, dist2, length );
        if( d < dist1 )
        {
            // ������� ������ ���������� ������������
            dist2 = dist1;
            dist1 = d;
            neighbor = i;
        }
        else if ( d < dist2 )
            dist2 = d;
    }
    if ( dist1 < 0.6*dist2 )
        return neighbor;
    return -1;
}
// ������� ���� ����������� ����
void CvSURF::findPairs( const CvSeq* objectKeypoints, const CvSeq* objectDescriptors,
           const CvSeq* imageKeypoints, const CvSeq* imageDescriptors, vector<int>& ptpairs )
{
    int i;
    CvSeqReader reader, kreader;
    // ��������� ��������� ����������� ������� �������������
    cvStartReadSeq( objectKeypoints, &kreader );
    cvStartReadSeq( objectDescriptors, &reader );
    ptpairs.clear();
    // ������� ���� �������������� �������
    for( i = 0; i < objectDescriptors->total; i++ )
    {
        const CvSURFPoint* kp = (const CvSURFPoint*)kreader.ptr;
        const float* descriptor = (const float*)reader.ptr;
        CV_NEXT_SEQ_ELEM( kreader.seq->elem_size, kreader );
        CV_NEXT_SEQ_ELEM( reader.seq->elem_size, reader );
        // ��������� ������� ����������� �� ����� ������������� �� �����
        int nearest_neighbor = naiveNearestNeighbor( descriptor, kp->laplacian, imageKeypoints, imageDescriptors );
        if( nearest_neighbor >= 0 )
        {
            // ������� ���������� ������������
            ptpairs.push_back(i);
            ptpairs.push_back(nearest_neighbor);
        }
    }
}
int CvSURF::locatePlanarObject( const CvSeq* objectKeypoints, const CvSeq* objectDescriptors,
                    const CvSeq* imageKeypoints, const CvSeq* imageDescriptors,
                    const CvPoint src_corners[4], CvPoint dst_corners[4] )
{
    double h[9];
    CvMat _h = cvMat(3, 3, CV_64F, h);
    vector<int> ptpairs;
    vector<CvPoint2D32f> pt1, pt2;
    CvMat _pt1, _pt2;
    int i, n;
    // ���� ���� ������������ �� ����� ���������, ������� �������������
    // ���� �����
    findPairs( objectKeypoints, objectDescriptors, imageKeypoints, imageDescriptors, ptpairs );
    n = ptpairs.size()/2;
    // ���� ��� ����, ������ ���� �������� - ������ �� ������
    if( n < 4 )
        return 0;
    // �������� ������
    pt1.resize(n);
    pt2.resize(n);
    // ��������� ���������� �������������
    for( i = 0; i < n; i++ )
    {
        pt1[i] = ((CvSURFPoint*)cvGetSeqElem(objectKeypoints,ptpairs[i*2]))->pt;
        pt2[i] = ((CvSURFPoint*)cvGetSeqElem(imageKeypoints,ptpairs[i*2+1]))->pt;
    }
    // �� ���������� �������� ������ ������
    _pt1 = cvMat(1, n, CV_32FC2, &pt1[0] );
    _pt2 = cvMat(1, n, CV_32FC2, &pt2[0] );
    // ������� ������������� ����� �������� ������������ � � ���, �������
    // ����
    if( !cvFindHomography( &_pt1, &_pt2, &_h, CV_RANSAC, 5 ))
        return 0;
    // �� ����������� �������� ������������� (� ������� _h) �������
    // ���������� ���������������, ���������������� ������
    for( i = 0; i < 4; i++ )
    {
        double x = src_corners[i].x, y = src_corners[i].y;
        double Z = 1./(h[6]*x + h[7]*y + h[8]);
        double X = (h[0]*x + h[1]*y + h[2])*Z;
        double Y = (h[3]*x + h[4]*y + h[5])*Z;
        dst_corners[i] = cvPoint(cvRound(X), cvRound(Y));
    }
    return 1;
}
CvSURF::~CvSURF(void)
{
}
