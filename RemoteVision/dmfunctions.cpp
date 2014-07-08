#include "dmfunctions.h"

#include <ctime>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include "nearestneighbour.h"


using namespace cv;
using namespace std;

DMFunctions::DMFunctions(){ init(); }

void DMFunctions::init()
{
    //cout << "Extracting training images\n";
    //UbyteExtractor e;

    //e.convert();

    //Train();
    //hashtbl = new vector<string>[11];
    //nn = new neuralNetwork(408, 1, 1);

    //nn->loadWeights("weights.csv");

    //Generate();

}

DMFunctions::~DMFunctions()
{
    if(nn != NULL)
    {
        delete nn;
    }
}

string DMFunctions::RecoginzeNum()
{
    dataReader dr;

    dr.loadDataFile("image.csv", 408, 1);

    vector<dataEntry*> d = dr.getAllDataEntries();
    return nn->feedForwardPattern(d.back()->pattern);
}

/*
void DMFunctions::Generate()
{
    fstream fin;
    cout << "Extracting Training Images\n";
    UbyteExtractor e;

    e.convert();
    fin.open("dataSet.csv");
    //take input file and hash it (open hashing)
    string line = "";
    while(getline(fin, line))
    {
        int i = hash(line);

        hashtbl[i].push_back(line);
    }
}

int DMFunctions::hash(string line)
{
    int sum = 0;
    for(int i = 0; i < line.length(); i++)
    {
        if(line[i] == ',' || line[i] == ' ')
        {
            continue;
        }
        sum += unsigned(line[i]);
    }

    int idx = sum % 11;
    return idx;
}
*/
int DMFunctions::DisplayVid(AL::ALValue& vPtr)
{
      /** Create an cv::Mat header to wrap into an opencv image.*/
      cv::Mat imgHeader = cv::Mat(cv::Size(320, 240), CV_8UC3);
      Mat imgGray = Mat(Size(320, 240), CV_8UC1);
      vector<vector<Point> > squares;

      //Create a OpenCV window to display the images.
      cv::namedWindow("images", WINDOW_AUTOSIZE);

      imgHeader.data = (uchar*) vPtr[6].GetBinary();

      detect(imgHeader);
      int ans = run();

      /*
      cvtColor(imgHeader, imgGray, CV_RGB2GRAY);

      Mat new_image = Mat::zeros(imgGray.size(), imgGray.type());
      Mat subMat = Mat::ones(imgGray.size(), imgGray.type()) * 255;

      subtract(subMat, imgGray, new_image);



      //imshow("images", new_image);


      find_squares(new_image, squares);
      drawSquares(new_image, squares);
      vectorize(new_image);
      /*
      find_squares(imgHeader, squares);
      drawSquares(imgHeader, squares);
      vectorize(imgHeader);*/

      return ans;
}

double DMFunctions::angle(Point pt1, Point pt2, Point pt0)
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

void DMFunctions::detect(Mat& occludedSquare)
{
    //Mat occludedSquare = imread("Square.jpg");

   //resize(occludedSquare, occludedSquare, Size(0, 0), 0.5, 0.5);

   Mat occludedSquare8u;
   cvtColor(occludedSquare, occludedSquare8u, CV_BGR2GRAY);

   //convert to a binary image. pixel values greater than 200 turn to white. otherwize black
   Mat thresh;
   threshold(occludedSquare8u, thresh, 170.0, 255.0, THRESH_BINARY);



   GaussianBlur(thresh, thresh, Size(7, 7), 2.0, 2.0);

   //Do edge detection
   Mat edges;
   Canny(thresh, edges, 30.0, 225.0, 3);\

   //remove the number from edge detection results
   vector<vector<Point> > contours;
   findContours(edges, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

   Mat zero = Mat::zeros(edges.size(), CV_8UC1);
   for(int i = 0; i < contours.size(); i++)
       drawContours(zero, contours, i, Scalar(255, 255, 255));

   //Do straight line detection
   vector<Vec2f> lines;
   HoughLines( zero, lines, .8, CV_PI/180, 35, 0, 0 );


   imshow("thresholded", zero);
   waitKey(10);


   cout << "Detected " << lines.size() << " lines." << endl;

   // compute the intersection from the lines detected...
   vector<Point2f> intersections;
   for( size_t i = 0; i < lines.size(); i++ )
   {
       for(size_t j = 0; j < lines.size(); j++)
       {
           Vec2f line1 = lines[i];
           Vec2f line2 = lines[j];
           if(acceptLinePair(line1, line2, CV_PI / 32)) //used to be pi / 32
           {
               Point2f intersection = computeIntersect(line1, line2);
               intersections.push_back(intersection);
           }
       }

   }

   if(intersections.size() > 0)
   {
       double smallestX = intersections[0].x, biggestY = intersections[0].y, biggestX = intersections[0].x, smallestY = intersections[0].y;
       vector<Point2f>::iterator i;
       for(i = intersections.begin(); i != intersections.end(); ++i)
       {
           //cout << "Intersection is " << i->x << ", " << i->y << endl;
           circle(occludedSquare, *i, 1, Scalar(0, 255, 0), 3);
       }

       imshow("intersect", occludedSquare);
       waitKey(10);

       for(i = intersections.begin(); i != intersections.end(); ++i)
       {
           if(smallestX > i->x && i->x >= 0)
           {
               smallestX = i->x;
           }
       }

       for(i = intersections.begin(); i != intersections.end(); ++i)
       {
           if(smallestY > i->y && i->y >= 0)
           {
               smallestY = i->y;
           }
       }

       for(i = intersections.begin(); i != intersections.end(); ++i)
       {
           if(biggestX < i->x && i->x < 320)
           {
               biggestX = i->x;
           }
       }

       for(i = intersections.begin(); i != intersections.end(); ++i)
       {
           if(biggestY < i->y && i->y < 240)
           {
               biggestY = i->y;
           }
       }
       try
       {
           Rect ROI(smallestX, smallestY, biggestX - smallestX, biggestY - smallestY);
           cout << ROI.x << " " << ROI.y << " " << ROI.width << " " << ROI.height << "\n";
           Mat localized = occludedSquare8u(ROI);

           imshow("localized", localized);
           waitKey(10);

           //Convert to correct Format
           Mat formatted = Mat::zeros(localized.size(), localized.type());
           Mat subMat = Mat::ones(localized.size(), localized.type()) * 255;

           subtract(subMat, localized, formatted);


           //threshold(formatted, formatted, 60, 0, THRESH_TOZERO);
           threshold(formatted,formatted, 65, 255, THRESH_BINARY);



           double eSize = .5;
           Mat ele = getStructuringElement(MORPH_RECT, Size(2 * eSize + 1, 2 * eSize + 2));
           dilate(formatted, formatted, ele);

           medianBlur(formatted, formatted, 3);
           //make border

           //top
           for(int i = 0; i < 10; i++)
           {
               for(int j = 0; j < formatted.cols; j++)
               {
                   formatted.at<uchar>(i,j) = 0.0;
               }
           }
           //bottom
           for(int i = formatted.rows - 10; i < formatted.rows; i++)
           {
               for(int j = 0; j < formatted.cols; j++)
               {
                   formatted.at<uchar>(i,j) = 0.0;
               }
           }
           //left
           for(int i = 0; i < formatted.rows; i++)
           {
               for(int j = 0; j < 10; j++)
               {
                   formatted.at<uchar>(i,j) = 0.0;
               }
           }
           //right
           for(int i = 0; i < formatted.rows; i++)
           {
               for(int j = formatted.cols - 10; j < formatted.cols; j++)
               {
                   formatted.at<uchar>(i, j) = 0.0;
               }
           }

           medianBlur(formatted, formatted, 5);

           //cut ROI that's just the image of interest!

           imshow("Formatted", formatted);
           waitKey(10);


           //Apply the Radon Transform
           //resize(formatted, formatted,Size(28, 28));

           imshow("Resized", formatted);
           waitKey(10);

           vector<pixel> radon;

           for(int r=0;r<formatted.rows;++r)
           {
               for(int c=0;c<formatted.cols;++c)
               {
                   if(formatted.at<uchar>(r, c) >= 1)
                   {
                       //we don't care what the pixel value is. This is in essence building a binary image
                       pixel idx;
                       idx.x = r;
                       idx.y = c;
                       radon.push_back(idx);
                       //DEBUG
                       //cout << "radon" << ".x: " << idx.x << "\tradon" <<".y: " <<idx.y << "\n";
                   }
               }
           }

           radonTransformer rT;

           float* preProcessed;
           //ofstream fo("Training_Data.csv", ios_base::app | ios_base::ate);
           ofstream fo("image.csv");
           rT.transform(radon);
           preProcessed = rT.getTotals();

           //cast 1d array to 2d array
           float (*pp)[11] = (float (*)[11]) preProcessed;


           //vectorize
           for(int j = 0; j < 8; j++)
           {
               for(int k = 0; k < 11; k++)
               {
                   fo << pp[j][k] << ", ";
               }
           }

/*
           //answer
           fo << "2\n";
           waitKey(15000);
*/
           fo.close();
       }
       catch(...)
       {
           //do nothing
       }
  }
}

bool DMFunctions::acceptLinePair(Vec2f line1, Vec2f line2, float minTheta)
{
    float theta1 = line1[1], theta2 = line2[1];

    if(theta1 < minTheta)
    {
        theta1 += CV_PI; // dealing with 0 and 180 ambiguities...
    }

    if(theta2 < minTheta)
    {
        theta2 += CV_PI; // dealing with 0 and 180 ambiguities...
    }

    return abs(theta1 - theta2) > minTheta;
}

// the long nasty wikipedia line-intersection equation...bleh...
Point2f DMFunctions::computeIntersect(Vec2f line1, Vec2f line2)
{
    vector<Point2f> p1 = lineToPointPair(line1);
    vector<Point2f> p2 = lineToPointPair(line2);

    float denom = (p1[0].x - p1[1].x)*(p2[0].y - p2[1].y) - (p1[0].y - p1[1].y)*(p2[0].x - p2[1].x);
    Point2f intersect(((p1[0].x*p1[1].y - p1[0].y*p1[1].x)*(p2[0].x - p2[1].x) -
                       (p1[0].x - p1[1].x)*(p2[0].x*p2[1].y - p2[0].y*p2[1].x)) / denom,
                      ((p1[0].x*p1[1].y - p1[0].y*p1[1].x)*(p2[0].y - p2[1].y) -
                       (p1[0].y - p1[1].y)*(p2[0].x*p2[1].y - p2[0].y*p2[1].x)) / denom);

    return intersect;
}

vector<Point2f> DMFunctions::lineToPointPair(Vec2f line)
{
    vector<Point2f> points;

    float r = line[0], t = line[1];
    double cos_t = cos(t), sin_t = sin(t);
    double x0 = r*cos_t, y0 = r*sin_t;
    double alpha = 1000;

    points.push_back(Point2f(x0 + alpha*(-sin_t), y0 + alpha*cos_t));
    points.push_back(Point2f(x0 - alpha*(-sin_t), y0 - alpha*cos_t));

    return points;
}

void DMFunctions::find_squares(Mat& image, vector<vector<Point> >& squares)
{
    // blur will enhance edge detection
    Mat blurred(image);
    medianBlur(image, blurred, 7);

    Mat gray0(blurred.size(), CV_8U), gray;
    vector<vector<Point> > contours;

    // find squares in every color plane of the image
    for (int c = 0; c < 1; c++)
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
                Canny(gray0, gray, 35, 110, 3);

                // Dilate helps to remove potential holes between edge segments
                dilate(gray, gray, Mat(), Point(-1,-1));
                imshow("images", gray);
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
            //drawContours(mask, squares, i, Scalar(0), CV_FILLED);
            Mat imageROI;

            image.copyTo(imageROI, mask);

            image = imageROI(roi);
        }
        catch(...)
        {
            //DO NOTHING. Bunches of errors, but It works lol
        }
    }

    //imshow("images", image);
}


void DMFunctions::vectorize(Mat& img)
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

    ofstream fo;

    fo.flush();

    fo.open("image.csv");


    resize(img,img,Size(28, 28));
    imshow("Resized", img);
    waitKey(10);

    //get pixel data
    uint8_t* pixelPtr = (uint8_t*)img.data;
    int cn = img.channels();

    //Apply Radon Transform

    for(int i = 0; i < img.rows; i++)
    {
        for(int j = 0; j < img.cols; j += cn)
        {
            uint8_t Pixel;
            Pixel = pixelPtr[i*img.cols*cn + j*cn];

            // do something with value...
            fo << (int)Pixel << ", ";
            fo.flush();
        }
    }

    //for running the network it doesn't matter what the answer is
    fo << answers[1] << endl;
    fo.flush();
    fo.close();

}

int DMFunctions::run()
{
    NearestNeighbour NN(7, 88);

    //NN.learn("Training_Data.csv", "image.csv", true);
    int ans = NN.learn("dataSet.csv", "image.csv", true);

    return ans;

}

void DMFunctions::Train()
{
    srand(time(NULL));

    //cout << "Extracting Training Images\n";
    //UbyteExtractor e;

    //e.convert();

    cout << "Making Data Reader\n";
    dataReader d;
    d.loadDataFile("Training_Data.csv", 88, 1);
    //d.loadDataFile("dataSet.csv", 408, 1);

    d.setCreationApproach(GROWING, 10);

    cout << "Configured Neural Network\n";
    neuralNetwork nn(88, 11, 1);

    cout << "Neural Trainer\n";
    neuralNetworkTrainer nT(&nn);

    nT.setTrainingParameters(.4, 0.9, false);
    nT.setStoppingConditions(20, 75);
    nT.enableLogging("log.csv", 5);
    cout << "Neural Trainer complete\n";

    cout << "Opening log file\n";
    fstream log("log.txt", ios_base::app | ios_base::ate);

    cout << "Opened\n";
    //train neural network on data sets
    for (int i=0; i < d.getNumTrainingSets(); i++ )
    {
        cout << "Starting training set " << i << endl;
        log << "Starting training set " << i << endl;
        nT.trainNetwork( d.getTrainingDataSet() );
        nn.saveWeights("intermediate_w.csv");
    }

    //save the weights
    nn.saveWeights("weights.csv");
    log.close();
}
