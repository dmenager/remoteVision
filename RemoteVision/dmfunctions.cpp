#include "dmfunctions.h"

using namespace cv;

DMFunctions::DMFunctions()
{

}

void DMFunctions::DisplayVid(AL::ALValue& vPtr)
{
      /** Create an cv::Mat header to wrap into an opencv image.*/
      cv::Mat imgHeader = cv::Mat(cv::Size(320, 240), CV_8UC3);

      //Create a OpenCV window to display the images.
      cv::namedWindow("images", WINDOW_AUTOSIZE);

      imgHeader.data = (uchar*) vPtr[6].GetBinary();

      imshow("images", imgHeader);
      cv::waitKey(0);
}
