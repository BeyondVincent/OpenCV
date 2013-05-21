#include "stdafx.h"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

int main()
{
  VideoCapture cap(1);

  if (!cap.isOpened())
    {
      cout <<"Failed to initialize camera\n";
      return 1;
    }

  namedWindow("CameraCapture");

  Mat frame;
  while (1)
    {
      cap>> frame;
      imshow("cameraCapture",frame);
      if (waitKey(30)>0)break;
    }
  destroyAllWindows();

  return 0;
}