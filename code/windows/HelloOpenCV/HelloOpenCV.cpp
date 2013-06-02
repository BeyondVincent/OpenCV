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

	//此函数等待按键，按键盘任意键就返回   
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
	//创建窗口
	cvNamedWindow("Video", 1);

	int nFrmNum = 0;
	//声明IplImage指针
	IplImage* pFrame = NULL;
	while(pFrame = cvQueryFrame( pCapture ))
	{
		nFrmNum++;
		//显示图像
		cvShowImage("Video", pFrame);

		//如果有按键事件，则跳出循环
		//此等待也为cvShowImage函数提供时间完成显示
		//等待时间可以根据CPU速度调整
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
	//创建窗口
	cvNamedWindow("Video", 1);

	int nFrmNum = 0;
	//声明IplImage指针
	IplImage* pFrame = NULL;
	while(pFrame = cvQueryFrame( pCapture ))
	{
		nFrmNum++;
		//显示图像
		cvShowImage("Video", pFrame);

		//如果有按键事件，则跳出循环
		//此等待也为cvShowImage函数提供时间完成显示
		//等待时间可以根据CPU速度调整
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

	//创建窗口
	cvNamedWindow("Video", 1);

	int nFrmNum = 0;
	//声明IplImage指针
	IplImage* pFrame = NULL;
	IplImage* bFrame = NULL;
	IplImage* fFrame = NULL;
	IplImage* resFrame = NULL;
	fFrame = cvCreateImage(cvSize( image_width,image_height), IPL_DEPTH_8U , 3);
	resFrame = cvCreateImage(cvSize( image_width,image_height), IPL_DEPTH_8U , 1);


	while(pFrame = cvQueryFrame( pCapture ))
	{
		nFrmNum++;
		//显示图像
		cvShowImage("Video", pFrame);

		//如果有按键事件，则跳出循环
		//此等待也为cvShowImage函数提供时间完成显示
		//等待时间可以根据CPU速度调整
		if( cvWaitKey(30) >= 0 )
		{
			if (bFrame == NULL)
			{
				bFrame = cvCreateImage(cvSize( image_width,image_height), IPL_DEPTH_8U , 3);
				cvCopy(pFrame, bFrame);
				cvShowImage("背景图", bFrame);

			} else {
				cvAbsDiff(bFrame, pFrame, fFrame);
				cvShowImage("前景图", fFrame);

				cvCvtColor(fFrame, resFrame, CV_RGB2GRAY);
				cvThreshold(resFrame, resFrame, 50, 255, CV_THRESH_BINARY);
				cvShowImage("前景图灰度化", resFrame);
			}
		}
	}
}

/// 全局变量
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

  /// 腐蚀操作
  erode( src, erosion_dst, element );
  imshow( "腐蚀", erosion_dst );
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
  ///膨胀操作
  dilate( src, dilation_dst, element );
  imshow( "膨胀", dilation_dst );
}

void MorphologyOpen( int, void* )
{
	 //使用开运算  
	Mat opened;  

	int open_type;
	if( open_elem == 0 ){ open_type = MORPH_RECT; }
	else if( open_elem == 1 ){ open_type = MORPH_CROSS; }
	else if( open_elem == 2) { open_type = MORPH_ELLIPSE; }

	Mat element = getStructuringElement( open_type,
		Size( 2*open_size + 1, 2*open_size+1 ),
		Point( open_size, open_size ) );
	morphologyEx(src,opened,cv::MORPH_OPEN,element);  

	imshow("开运算",opened); 
}

void MorphologyClose( int, void* )
{
	//使用闭运算  
	Mat closed;  

	int close_type;
	if( close_elem == 0 ){ close_type = MORPH_RECT; }
	else if( close_elem == 1 ){ close_type = MORPH_CROSS; }
	else if( close_elem == 2) { close_type = MORPH_ELLIPSE; }

	Mat element = getStructuringElement( close_type,
		Size( 2*close_size + 1, 2*close_size+1 ),
		Point( close_size, close_size ) );
	morphologyEx(src,closed,cv::MORPH_CLOSE,element);  

	imshow("闭运算",closed); 
}

void ErosionAndDilation()
{
	  /// Load 图像
  src = imread("close.jpg");

  if( !src.data )
  { return ; }

  /// 创建显示窗口
  namedWindow( "腐蚀", CV_WINDOW_AUTOSIZE );
  namedWindow( "膨胀", CV_WINDOW_AUTOSIZE );
  namedWindow( "开运算", CV_WINDOW_AUTOSIZE );
  namedWindow( "闭运算", CV_WINDOW_AUTOSIZE );
  cvMoveWindow( "Dilation Demo", src.cols, 0 );

  /// 创建腐蚀 Trackbar
  createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "腐蚀",
                  &erosion_elem, max_elem,
                  Erosion );

  createTrackbar( "Kernel size:\n 2n +1", "腐蚀",
                  &erosion_size, max_kernel_size,
                  Erosion );

  /// 创建膨胀 Trackbar
  createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "膨胀",
                  &dilation_elem, max_elem,
                  Dilation );

  createTrackbar( "Kernel size:\n 2n +1", "膨胀",
                  &dilation_size, max_kernel_size,
                  Dilation );

    /// 创建开运算 Trackbar
  createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "开运算",
                  &open_elem, max_elem,
                  MorphologyOpen );

  createTrackbar( "Kernel size:\n 2n +1", "开运算",
                  &open_size, max_kernel_size,
                  MorphologyOpen );
  
    /// 创建闭运算 Trackbar
  createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "闭运算",
                  &close_elem, max_elem,
                  MorphologyClose );

  createTrackbar( "Kernel size:\n 2n +1", "闭运算",
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

	/// 装载图像
	src = imread("1.jpg");
	imshow("原图", src );

	if( !src.data )
	{ return; }

	/// 分割成3个单通道图像 ( R, G 和 B )
	vector<Mat> rgb_planes;
	split( src, rgb_planes );

	imshow("R", rgb_planes[0] );
	imshow("G", rgb_planes[1] );
	imshow("B", rgb_planes[2] );

	/// 设定bin数目
	int histSize = 255;

	/// 设定取值范围 ( R,G,B) )
	float range[] = { 0, 255 } ;
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat r_hist, g_hist, b_hist;

	/// 计算直方图:
	calcHist( &rgb_planes[0], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );
	calcHist( &rgb_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
	calcHist( &rgb_planes[2], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );

	// 创建直方图画布
	int hist_w = 400; int hist_h = 400;
	int bin_w = cvRound( (double) hist_w/histSize );

	Mat histImage( hist_w, hist_h, CV_8UC3, Scalar( 0,0,0) );

	/// 将直方图归一化到范围 [ 0, histImage.rows ]
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

	/// 在直方图画布上画出直方图
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

	/// 显示直方图
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
	imshow("calcHist Demo", histImage );

	waitKey(0);
}

void EqualizeHist()
{
	Mat src, dst;

	/// 装载图像
	src = imread("1.jpg");
	imshow("原图", src );

	if( !src.data )
	{ return; }

	/// 分割成3个单通道图像 ( R, G 和 B )
	vector<Mat> rgb_planes;
	split( src, rgb_planes );

	/// 设定bin数目
	int histSize = 255;

	/// 设定取值范围 ( R,G,B) )
	float range[] = { 0, 255 } ;
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat r_hist, g_hist, b_hist;

	/// 计算直方图:
	calcHist( &rgb_planes[0], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );
	calcHist( &rgb_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
	calcHist( &rgb_planes[2], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );

	// 创建直方图画布
	int hist_w = 400; int hist_h = 400;
	int bin_w = cvRound( (double) hist_w/histSize );

	Mat histImage( hist_w, hist_h, CV_8UC3, Scalar( 0,0,0) );

	/// 将直方图归一化到范围 [ 0, histImage.rows ]
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

	/// 在直方图画布上画出直方图
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

	/// 显示直方图
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
	imshow("calcHist Demo", histImage );

	waitKey(0);
}

// 均值滤波
void Blur()
{
	//载入图片
    IplImage *in = cvLoadImage("lvbo1.png");

    //创建显示窗口
    cvNamedWindow("In",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Out",CV_WINDOW_AUTOSIZE);

    //生成输出图片
    IplImage *out=cvCreateImage(cvGetSize(in), IPL_DEPTH_8U, 3);

    //对输出图像平滑处理
    cvSmooth( in, out, CV_MEDIAN, 5,5 );

    //显示图像
    cvShowImage("In",in);
    cvShowImage("Out",out);

    cvWaitKey();
    cvDestroyWindow("In");
    cvDestroyWindow("Out");
    cvReleaseImage(&in);
    cvReleaseImage(&out);
}

// 中值滤波
void MedianBlur ()
{
		//载入图片
    IplImage *in = cvLoadImage("lvbo1.png");

    //创建显示窗口
    cvNamedWindow("In",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Out",CV_WINDOW_AUTOSIZE);

    //生成输出图片
    IplImage *out=cvCreateImage(cvGetSize(in), IPL_DEPTH_8U, 3);

    //对输出图像平滑处理
    cvSmooth( in, out, CV_MEDIAN, 5,5);

    //显示图像
    cvShowImage("In",in);
    cvShowImage("Out",out);

    cvWaitKey();
    cvDestroyWindow("In");
    cvDestroyWindow("Out");
    cvReleaseImage(&in);
    cvReleaseImage(&out);
}

// 高斯滤波
void GaussianBlur()
{
			//载入图片
    IplImage *in = cvLoadImage("lvbo1.png");

    //创建显示窗口
    cvNamedWindow("In",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Out",CV_WINDOW_AUTOSIZE);

    //生成输出图片
    IplImage *out=cvCreateImage(cvGetSize(in), IPL_DEPTH_8U, 3);

    //对输出图像平滑处理
    cvSmooth( in, out, CV_GAUSSIAN, 5,5 );

    //显示图像
    cvShowImage("In",in);
    cvShowImage("Out",out);

    cvWaitKey();
    cvDestroyWindow("In");
    cvDestroyWindow("Out");
    cvReleaseImage(&in);
    cvReleaseImage(&out);
}

// 双边滤波
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
	// 显示图片
	/*showImage();
	return 0;*/

	// 加载视频
	//loadVideo();

	//保存图片
	//saveImage();

	// 图像差分
	//diffImage();
	 //OpenCVBaseType *baseType = new OpenCVBaseType();

	// 点数据结构
	//baseType->PointType();
	//baseType->DrawPolygon();

	// 腐蚀膨胀
	// ErosionAndDilation();

	// 直方图
	// HistImage();

	// 滤波
	// 均值滤波
	//Blur();

	// 中值滤波
	MedianBlur ();

	// 高斯滤波
	//GaussianBlur();

	// 双边滤波
	//BilateralFilter();

	// 运动目标检测
	ObjectDetect();
	return 0;
}