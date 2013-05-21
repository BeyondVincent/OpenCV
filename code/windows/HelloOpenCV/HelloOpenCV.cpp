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
	diffImage();
	return 0;
}