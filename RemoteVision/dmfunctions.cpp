#include "dmfunctions.h"
//#include "dataEntry.h"
//#include "dataReader.h"
#include "neuralNetwork.h"
#include "neuralNetworkTrainer.h"

#include <ctime>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <cstring>


using namespace cv;
using namespace std;
DMFunctions::DMFunctions()
{

}



void DMFunctions::DisplayVid(AL::ALValue& vPtr)
{
      /** Create an cv::Mat header to wrap into an opencv image.*/
      cv::Mat imgHeader = cv::Mat(cv::Size(320, 240), CV_8UC3);
      vector<vector<Point> > squares;

      //Create a OpenCV window to display the images.
      cv::namedWindow("images", WINDOW_AUTOSIZE);

      imgHeader.data = (uchar*) vPtr[6].GetBinary();

      find_squares(imgHeader, squares);
      drawSquares(imgHeader, squares);

      buildTrainingSet(imgHeader);
}

double DMFunctions::angle(Point pt1, Point pt2, Point pt0)
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}


void DMFunctions::find_squares(Mat& image, vector<vector<Point> >& squares)
{
    // blur will enhance edge detection
    Mat blurred(image);
    //medianBlur(image, blurred, 1);

    Mat gray0(blurred.size(), CV_8U), gray;
    vector<vector<Point> > contours;

    // find squares in every color plane of the image
    for (int c = 0; c < 3; c++)
    {
        int ch[] = {c, 0};
        mixChannels(&blurred, 1, &gray0, 1, ch, 1);

        // try several threshold levels
        const int threshold_level = 2;
        for (int l = 0; l < threshold_level; l++)
        {
            // Use Canny instead of zero threshold level!
            // Canny helps to catch squares with gradient shading
            if (l == 0)
            {
                Canny(gray0, gray, 10, 20, 3); //

                // Dilate helps to remove potential holes between edge segments
                dilate(gray, gray, Mat(), Point(-1,-1));
            }
            else
            {
                    gray = gray0 >= (l+1) * 255 / threshold_level;
            }

            // Find contours and store them in a list
            findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

            // Test contours
            vector<Point> approx;
            for (size_t i = 0; i < contours.size(); i++)
            {
                    // approximate contour with accuracy proportional
                    // to the contour perimeter
                    approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

                    // Note: absolute value of an area is used because
                    // area may be positive or negative - in accordance with the
                    // contour orientation
                    if (approx.size() == 4 &&
                            fabs(contourArea(Mat(approx))) > 1000 &&
                            isContourConvex(Mat(approx)))
                    {
                            double maxCosine = 0;

                            for (int j = 2; j < 5; j++)
                            {
                                    double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                                    maxCosine = MAX(maxCosine, cosine);
                            }

                            if (maxCosine < 0.25)
                                    squares.push_back(approx);
                    }
            }

        }
    }
}

// the function draws all the squares in the image
void DMFunctions::drawSquares( Mat& image, const vector<vector<Point> >& squares )
{
    for( size_t i = 0; i < squares.size(); i++ )
    {
        const Point* p = &squares[i][0];
        int n = (int)squares[i].size();
        polylines(image, &p, &n, 1, true, Scalar(0,255,0), 3, CV_AA);

        try
        {
            Rect roi = boundingRect(squares[i]);

            Mat mask = Mat::zeros(image.size(), CV_8UC1);
            drawContours(mask, squares, i, Scalar(255), CV_FILLED);

            Mat imageROI;

            image.copyTo(imageROI, mask);

            image = imageROI(roi);
        }
        catch(...)
        {
            //DO NOTHING. Bunches of errors, but It works lol
        }
    }

    imshow("images", image);
}


void DMFunctions::buildTrainingSet(Mat& img)
{
    string answers[10] =
    {"0, 0, 0, 0, 0, 0, 0, 0, 0, 0",
     "0, 0, 0, 0, 0, 0, 0, 0, 1, 0",
     "0, 0, 0, 0, 0, 0, 0, 1, 0, 0",
     "0, 0, 0, 0, 0, 0, 1, 0, 0, 0",
     "0, 0, 0, 0, 0, 1, 0, 0, 0, 0",
     "0, 0, 0, 0, 1, 0, 0, 0, 0, 0",
     "0, 0, 0, 1, 0, 0, 0, 0, 0, 0",
     "0, 0, 1, 0, 0, 0, 0, 0, 0, 0",
     "0, 1, 0, 0, 0, 0, 0, 0, 0, 0",
     "1, 0, 0, 0, 0, 0, 0, 0, 0, 0"};

    ofstream fo("customDataSet.csv", ios_base::ate | ios_base::app);
    //to grayscale
    cv::cvtColor(img, img, CV_BGR2GRAY);

    resize(img,img,Size(30, 30));

    //get pixel data
    uint8_t* pixelPtr = (uint8_t*)img.data;
    int cn = img.channels();
    for(int i = 0; i < img.rows; i++)
    {
        for(int j = 0; j < img.cols; j += cn)
        {
            uint8_t Pixel;
            Pixel = pixelPtr[i*img.cols*cn + j*cn];

            // do something with value...
            fo << (int)Pixel << ", ";
        }
    }

    fo << answers[0];
    fo << "\n";
    fo.close();
    sleep(5);
}
