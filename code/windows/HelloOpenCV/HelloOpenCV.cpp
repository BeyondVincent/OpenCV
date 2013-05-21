#include "stdafx.h"
#include <iostream>

#include <opencv2\opencv.hpp>

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
	diffImage();
	return 0;
}