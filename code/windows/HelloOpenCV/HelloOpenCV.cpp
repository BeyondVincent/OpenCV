#include "stdafx.h"
#include <iostream>

#include "highgui.h"
#include <cv.h>
#include <cxcore.h>
#include <cvaux.h>

#include <opencv2\opencv.hpp>
#include "OpenCVBaseType.h"

using namespace cv;
using namespace std;

void showImage()
{
	const char* fileName = "1.jpg";  

	cvNamedWindow("win1", CV_WINDOW_AUTOSIZE); 

	cvMoveWindow("win1", 500, 500); // offset from the UL corner of the screen

	IplImage* img=0; 
	img=cvLoadImage(fileName);

	if(!img) 
	{
		printf("Could not load image file: %s\n",fileName);

	} else {
	cvShowImage("win1",img);
	}

	//�˺����ȴ�������������������ͷ���   
	cvWaitKey();  

	cvDestroyWindow("win1");
}

void loadVideo()
{
	CvCapture* pCapture = NULL;
	//if(!(pCapture = cvCaptureFromFile("1.wmv")))
	if(!(pCapture = cvCaptureFromCAM(0)))
	{
		return;
	}
	//��������
	cvNamedWindow("Video", 1);

	int nFrmNum = 0;
	//����IplImageָ��
	IplImage* pFrame = NULL;
	while(pFrame = cvQueryFrame( pCapture ))
	{
		nFrmNum++;
		//��ʾͼ��
		cvShowImage("Video", pFrame);

		//����а����¼���������ѭ��
		//�˵ȴ�ҲΪcvShowImage�����ṩʱ�������ʾ
		//�ȴ�ʱ����Ը���CPU�ٶȵ���
		if( cvWaitKey(5) >= 0 )
			break;
	}
}

char * StringConnection(char *s1,char *s2){
	int i=strlen(s1);//StringLength(s1);
	int j=strlen(s2);//StringLength(s2);
	char *pc=(char *)malloc(i+j+1);
	char *pc1;
	pc1=pc;
	while((*pc++=*s1++)!='\0');
	pc--;
	while((*pc++=*s2++)!='\0');
	return pc1;
}

void saveImage()
{
	CvCapture* pCapture = NULL;
	//if(!(pCapture = cvCaptureFromFile("1.wmv")))
	if(!(pCapture = cvCaptureFromCAM(0)))
	{
		return;
	}
	//��������
	cvNamedWindow("Video", 1);

	int nFrmNum = 0;
	//����IplImageָ��
	IplImage* pFrame = NULL;
	while(pFrame = cvQueryFrame( pCapture ))
	{
		nFrmNum++;
		//��ʾͼ��
		cvShowImage("Video", pFrame);

		//����а����¼���������ѭ��
		//�˵ȴ�ҲΪcvShowImage�����ṩʱ�������ʾ
		//�ȴ�ʱ����Ը���CPU�ٶȵ���
		if( cvWaitKey(30) >= 0 )
		{
			char str[15];
			char str2[] = ".png";
			sprintf_s(str, "%d", nFrmNum);
			cvSaveImage(StringConnection(str, str2), pFrame);

			cvShowImage("image", pFrame);
		}
	}
}

void diffImage()
{
	
	CvCapture* pCapture = NULL;
	if(!(pCapture = cvCaptureFromCAM(0)))
	{
		return;
	}

	 IplImage *frame=0;
	 frame=cvQueryFrame(pCapture);
	 int image_width=(int)frame->width;
	 int image_height=(int)frame->height;

	//��������
	cvNamedWindow("Video", 1);

	int nFrmNum = 0;
	//����IplImageָ��
	IplImage* pFrame = NULL;
	IplImage* bFrame = NULL;
	IplImage* fFrame = NULL;
	IplImage* resFrame = NULL;
	fFrame = cvCreateImage(cvSize( image_width,image_height), IPL_DEPTH_8U , 3);
	resFrame = cvCreateImage(cvSize( image_width,image_height), IPL_DEPTH_8U , 1);


	while(pFrame = cvQueryFrame( pCapture ))
	{
		nFrmNum++;
		//��ʾͼ��
		cvShowImage("Video", pFrame);

		//����а����¼���������ѭ��
		//�˵ȴ�ҲΪcvShowImage�����ṩʱ�������ʾ
		//�ȴ�ʱ����Ը���CPU�ٶȵ���
		if( cvWaitKey(30) >= 0 )
		{
			if (bFrame == NULL)
			{
				bFrame = cvCreateImage(cvSize( image_width,image_height), IPL_DEPTH_8U , 3);
				cvCopy(pFrame, bFrame);
				cvShowImage("����ͼ", bFrame);

			} else {
				cvAbsDiff(bFrame, pFrame, fFrame);
				cvShowImage("ǰ��ͼ", fFrame);

				cvCvtColor(fFrame, resFrame, CV_RGB2GRAY);
				cvThreshold(resFrame, resFrame, 50, 255, CV_THRESH_BINARY);
				cvShowImage("ǰ��ͼ�ҶȻ�", resFrame);
			}
		}
	}
}

/// ȫ�ֱ���
Mat src, erosion_dst, dilation_dst;

int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int open_elem = 0;
int open_size = 0;
int close_elem = 0;
int close_size = 0;

int const max_elem = 2;
int const max_kernel_size = 50;

/** Function Headers */
void Erosion( int, void* );
void Dilation( int, void* );

/**  @function Erosion  */
void Erosion( int, void* )
{
  int erosion_type;
  if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
  else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
  else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

  Mat element = getStructuringElement( erosion_type,
                                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                       Point( erosion_size, erosion_size ) );

  /// ��ʴ����
  erode( src, erosion_dst, element );
  imshow( "��ʴ", erosion_dst );
}

/** @function Dilation */
void Dilation( int, void* )
{
  int dilation_type;
  if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
  else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
  else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

  Mat element = getStructuringElement( dilation_type,
                                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                       Point( dilation_size, dilation_size ) );
  ///���Ͳ���
  dilate( src, dilation_dst, element );
  imshow( "����", dilation_dst );
}

void MorphologyOpen( int, void* )
{
	 //ʹ�ÿ�����  
	Mat opened;  

	int open_type;
	if( open_elem == 0 ){ open_type = MORPH_RECT; }
	else if( open_elem == 1 ){ open_type = MORPH_CROSS; }
	else if( open_elem == 2) { open_type = MORPH_ELLIPSE; }

	Mat element = getStructuringElement( open_type,
		Size( 2*open_size + 1, 2*open_size+1 ),
		Point( open_size, open_size ) );
	morphologyEx(src,opened,cv::MORPH_OPEN,element);  

	imshow("������",opened); 
}

void MorphologyClose( int, void* )
{
	//ʹ�ñ�����  
	Mat closed;  

	int close_type;
	if( close_elem == 0 ){ close_type = MORPH_RECT; }
	else if( close_elem == 1 ){ close_type = MORPH_CROSS; }
	else if( close_elem == 2) { close_type = MORPH_ELLIPSE; }

	Mat element = getStructuringElement( close_type,
		Size( 2*close_size + 1, 2*close_size+1 ),
		Point( close_size, close_size ) );
	morphologyEx(src,closed,cv::MORPH_CLOSE,element);  

	imshow("������",closed); 
}

void ErosionAndDilation()
{
	  /// Load ͼ��
  src = imread("close.jpg");

  if( !src.data )
  { return ; }

  /// ������ʾ����
  namedWindow( "��ʴ", CV_WINDOW_AUTOSIZE );
  namedWindow( "����", CV_WINDOW_AUTOSIZE );
  namedWindow( "������", CV_WINDOW_AUTOSIZE );
  namedWindow( "������", CV_WINDOW_AUTOSIZE );
  cvMoveWindow( "Dilation Demo", src.cols, 0 );

  /// ������ʴ Trackbar
  createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "��ʴ",
                  &erosion_elem, max_elem,
                  Erosion );

  createTrackbar( "Kernel size:\n 2n +1", "��ʴ",
                  &erosion_size, max_kernel_size,
                  Erosion );

  /// �������� Trackbar
  createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "����",
                  &dilation_elem, max_elem,
                  Dilation );

  createTrackbar( "Kernel size:\n 2n +1", "����",
                  &dilation_size, max_kernel_size,
                  Dilation );

    /// ���������� Trackbar
  createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "������",
                  &open_elem, max_elem,
                  MorphologyOpen );

  createTrackbar( "Kernel size:\n 2n +1", "������",
                  &open_size, max_kernel_size,
                  MorphologyOpen );
  
    /// ���������� Trackbar
  createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "������",
                  &close_elem, max_elem,
                  MorphologyClose );

  createTrackbar( "Kernel size:\n 2n +1", "������",
                  &close_size, max_kernel_size,
                  MorphologyClose );
  /// Default start
  Erosion( 0, 0 );
  Dilation( 0, 0 );

  MorphologyOpen(0, 0);
  MorphologyClose(0, 0);

  waitKey(0);
}

void HistImage()
{
	Mat src, dst;

	/// װ��ͼ��
	src = imread("1.jpg");
	imshow("ԭͼ", src );

	if( !src.data )
	{ return; }

	/// �ָ��3����ͨ��ͼ�� ( R, G �� B )
	vector<Mat> rgb_planes;
	split( src, rgb_planes );

	imshow("R", rgb_planes[0] );
	imshow("G", rgb_planes[1] );
	imshow("B", rgb_planes[2] );

	/// �趨bin��Ŀ
	int histSize = 255;

	/// �趨ȡֵ��Χ ( R,G,B) )
	float range[] = { 0, 255 } ;
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat r_hist, g_hist, b_hist;

	/// ����ֱ��ͼ:
	calcHist( &rgb_planes[0], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );
	calcHist( &rgb_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
	calcHist( &rgb_planes[2], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );

	// ����ֱ��ͼ����
	int hist_w = 400; int hist_h = 400;
	int bin_w = cvRound( (double) hist_w/histSize );

	Mat histImage( hist_w, hist_h, CV_8UC3, Scalar( 0,0,0) );

	/// ��ֱ��ͼ��һ������Χ [ 0, histImage.rows ]
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

	/// ��ֱ��ͼ�����ϻ���ֱ��ͼ
	for( int i = 1; i < histSize; i++ )
	{
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
			Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
			Scalar( 0, 0, 255), 2, 8, 0  );
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
			Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
			Scalar( 0, 255, 0), 2, 8, 0  );
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
			Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
			Scalar( 255, 0, 0), 2, 8, 0  );
	}

	/// ��ʾֱ��ͼ
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
	imshow("calcHist Demo", histImage );

	waitKey(0);
}

void EqualizeHist()
{
	Mat src, dst;

	/// װ��ͼ��
	src = imread("1.jpg");
	imshow("ԭͼ", src );

	if( !src.data )
	{ return; }

	/// �ָ��3����ͨ��ͼ�� ( R, G �� B )
	vector<Mat> rgb_planes;
	split( src, rgb_planes );

	/// �趨bin��Ŀ
	int histSize = 255;

	/// �趨ȡֵ��Χ ( R,G,B) )
	float range[] = { 0, 255 } ;
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat r_hist, g_hist, b_hist;

	/// ����ֱ��ͼ:
	calcHist( &rgb_planes[0], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );
	calcHist( &rgb_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
	calcHist( &rgb_planes[2], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );

	// ����ֱ��ͼ����
	int hist_w = 400; int hist_h = 400;
	int bin_w = cvRound( (double) hist_w/histSize );

	Mat histImage( hist_w, hist_h, CV_8UC3, Scalar( 0,0,0) );

	/// ��ֱ��ͼ��һ������Χ [ 0, histImage.rows ]
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

	/// ��ֱ��ͼ�����ϻ���ֱ��ͼ
	for( int i = 1; i < histSize; i++ )
	{
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
			Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
			Scalar( 0, 0, 255), 2, 8, 0  );
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
			Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
			Scalar( 0, 255, 0), 2, 8, 0  );
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
			Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
			Scalar( 255, 0, 0), 2, 8, 0  );
	}

	/// ��ʾֱ��ͼ
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
	imshow("calcHist Demo", histImage );

	waitKey(0);
}

// ��ֵ�˲�
void Blur()
{
	//����ͼƬ
    IplImage *in = cvLoadImage("lvbo1.png");

    //������ʾ����
    cvNamedWindow("In",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Out",CV_WINDOW_AUTOSIZE);

    //�������ͼƬ
    IplImage *out=cvCreateImage(cvGetSize(in), IPL_DEPTH_8U, 3);

    //�����ͼ��ƽ������
    cvSmooth( in, out, CV_MEDIAN, 5,5 );

    //��ʾͼ��
    cvShowImage("In",in);
    cvShowImage("Out",out);

    cvWaitKey();
    cvDestroyWindow("In");
    cvDestroyWindow("Out");
    cvReleaseImage(&in);
    cvReleaseImage(&out);
}

// ��ֵ�˲�
void MedianBlur ()
{
		//����ͼƬ
    IplImage *in = cvLoadImage("lvbo1.png");

    //������ʾ����
    cvNamedWindow("In",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Out",CV_WINDOW_AUTOSIZE);

    //�������ͼƬ
    IplImage *out=cvCreateImage(cvGetSize(in), IPL_DEPTH_8U, 3);

    //�����ͼ��ƽ������
    cvSmooth( in, out, CV_MEDIAN, 5,5);

    //��ʾͼ��
    cvShowImage("In",in);
    cvShowImage("Out",out);

    cvWaitKey();
    cvDestroyWindow("In");
    cvDestroyWindow("Out");
    cvReleaseImage(&in);
    cvReleaseImage(&out);
}

// ��˹�˲�
void GaussianBlur()
{
			//����ͼƬ
    IplImage *in = cvLoadImage("lvbo1.png");

    //������ʾ����
    cvNamedWindow("In",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Out",CV_WINDOW_AUTOSIZE);

    //�������ͼƬ
    IplImage *out=cvCreateImage(cvGetSize(in), IPL_DEPTH_8U, 3);

    //�����ͼ��ƽ������
    cvSmooth( in, out, CV_GAUSSIAN, 5,5 );

    //��ʾͼ��
    cvShowImage("In",in);
    cvShowImage("Out",out);

    cvWaitKey();
    cvDestroyWindow("In");
    cvDestroyWindow("Out");
    cvReleaseImage(&in);
    cvReleaseImage(&out);
}

// ˫���˲�
void BilateralFilter()
{

}
void ObjectDetect()
{
	CvCapture* pCapture = NULL;
	if(!(pCapture = cvCaptureFromFile("highwayII_raw.AVI")))
	{
		return;
	}

	 /* Capture 1 video frame for initialization */  
    IplImage* videoFrame = NULL;  
    videoFrame = cvQueryFrame(pCapture);  
  
    if(!videoFrame)  
    {  
        printf("Bad frame /n");  
        exit(0);  
    }  
  
    // Create windows  
    cvNamedWindow("BG", 1);  
    cvNamedWindow("FG", 1);  
  
    // Select parameters for Gaussian model.  
    CvGaussBGStatModelParams* params = new CvGaussBGStatModelParams;                          
    params->win_size=2;      
    params->n_gauss=5;  
    params->bg_threshold=0.3;
    params->std_threshold=3.5;  
    params->minArea=15;  
    params->weight_init=0.05;  
    params->variance_init=30;   

    CvBGStatModel* bgModel = cvCreateGaussianBGModel(videoFrame ,params);  
  
    int key=-1;  
    while(key != 'q')  
    {  
        // Grab a fram  
        videoFrame = cvQueryFrame(pCapture);  
        if( !videoFrame )  
            break;  
          
        // Update model  
        cvUpdateBGStatModel(videoFrame,bgModel);  
          
        // Display results  
           cvShowImage("BG", bgModel->background);  
           cvShowImage("FG", bgModel->foreground);    
		   cvShowImage("org", videoFrame);      

           key = cvWaitKey(10);  
    }  
  
    cvDestroyWindow("BG");  
    cvDestroyWindow("FG");  
    cvReleaseBGStatModel( &bgModel );  
    cvReleaseCapture(&pCapture);   
}

int main()
{
	// ��ʾͼƬ
	/*showImage();
	return 0;*/

	// ������Ƶ
	//loadVideo();

	//����ͼƬ
	//saveImage();

	// ͼ����
	//diffImage();
	 //OpenCVBaseType *baseType = new OpenCVBaseType();

	// �����ݽṹ
	//baseType->PointType();
	//baseType->DrawPolygon();

	// ��ʴ����
	// ErosionAndDilation();

	// ֱ��ͼ
	// HistImage();

	// �˲�
	// ��ֵ�˲�
	//Blur();

	// ��ֵ�˲�
	MedianBlur ();

	// ��˹�˲�
	//GaussianBlur();

	// ˫���˲�
	//BilateralFilter();

	// �˶�Ŀ����
	ObjectDetect();
	return 0;
}