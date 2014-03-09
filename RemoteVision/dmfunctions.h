#ifndef DMFUNCTIONS_H
#define DMFUNCTIONS_H

#include <alvision/alvisiondefinitions.h>
#include <alvalue/alvalue.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <vector>

class DMFunctions
{
public:
    DMFunctions();
    void DisplayVid(AL::ALValue& vPtr);
private:
    void locateObj();
    void find_squares(cv::Mat& image, std::vector<std::vector<cv::Point> >& squares);
    double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0 );
    void drawSquares( cv::Mat& image, const std::vector<std::vector<cv::Point> >& squares );
};

#endif // DMFUNCTIONS_H
