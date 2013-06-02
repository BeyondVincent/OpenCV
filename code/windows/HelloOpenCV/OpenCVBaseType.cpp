#include "stdafx.h"
#include "OpenCVBaseType.h"

#include <opencv2\opencv.hpp>
#include "OpenCVBaseType.h"

using namespace cv;
using namespace std;

OpenCVBaseType::OpenCVBaseType(void)
{
}


OpenCVBaseType::~OpenCVBaseType(void)
{
}

void OpenCVBaseType::PointType(void)
{
	CvPoint Point1=cvPoint(300,200);  

	CvPoint2D32f Point2 = cvPoint2D32f(200.0,240.0);  
	CvPoint2D64f Point3 = cvPoint2D64f(100.0,300.0);  

	CvPoint3D32f Point4 = cvPoint3D32f(100.0,200.0,300.0);  
	CvPoint3D64f Point5 = cvPoint3D64f(100.0,100.0,100.0);  

	CvPoint2D32f Point6 = cvPointTo32f(Point1);
	CvPoint Point7 = cvPointFrom32f(Point6);  

	printf("2Î¬\n");  
	printf("Point1 : (%d ,%d)\n",Point1.x,Point1.y);  
	printf("Point2 : (%.1f,%.1f)\n",Point2.x,Point2.y);  
	printf("Point3 : (%.1f,%.1f)\n",Point3.x,Point3.y);  

	printf("\n3Î¬\n");  
	printf("Point4 : (%.1f,%.1f,%.1f)\n",Point4.x,Point4.y,Point4.z);  
	printf("Point5 : (%.1f,%.1f,%.1f)\n",Point5.x,Point5.y,Point5.z);  

	printf("\n×ª»»\n");  
	printf("Point6 : (%.1f,%.1f)\n",Point6.x,Point6.y);  
	printf("Point7 : (%d,%d)\n\n",Point7.x,Point7.y); 
}

void OpenCVBaseType::DrawPolygon(void)
{
	CvPoint PointArray1[6];  
	int PolyVertexNumber;  
	int Shift;  
	IplImage *Image1; 
	CvSize ImageSize1 = cvSize(1000,700);  
	Image1 = cvCreateImage(ImageSize1, IPL_DEPTH_8U, 3);  

	PointArray1[0]=cvPoint(200,200);  
	PointArray1[1]=cvPoint(400,150);  
	PointArray1[2]=cvPoint(300,230);  
	PointArray1[3]=cvPoint(800,300);  
	PointArray1[4]=cvPoint(900,550);  
	PointArray1[5]=cvPoint(100,500);  

	CvScalar Color=CV_RGB(123,57,120);  
	PolyVertexNumber=6;  
	Shift=0;  

	cvFillConvexPoly(Image1,PointArray1,PolyVertexNumber,Color,CV_AA,Shift);  

	cvNamedWindow("FillConvexPoly",0);  
	cvShowImage("FillConvexPoly",Image1);  
	cvWaitKey(0);  
	cvSaveImage("poly.jpg",Image1);  
	cvReleaseImage(&Image1);   
}
