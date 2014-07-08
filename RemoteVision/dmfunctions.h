#ifndef DMFUNCTIONS_H
#define DMFUNCTIONS_H

#include <alcommon/almodule.h>
#include <alvision/alvisiondefinitions.h>
#include <alvalue/alvalue.h>
#include <alproxies/altexttospeechproxy.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>

#include "neuralNetwork.h"
#include "neuralNetworkTrainer.h"
#include "ubyteextractor.h"
#include "radonTransformer.h"
#include <cstring>
#include <stdlib.h>

#include <vector>

namespace AL
{
    class ALBroker;
}

class DMFunctions /*: public AL::ALModule */
{
public:
    /*DMFunctions(boost::shared_ptr<AL::ALBroker> broker,
                const std::string &name); */
    DMFunctions();
    virtual ~DMFunctions();
    virtual void init();
    int DisplayVid(AL::ALValue& vPtr);
    void Train();

    std::string RecoginzeNum();
private:
    void locateObj();
    void find_squares(cv::Mat& image, std::vector<std::vector<cv::Point> >& squares);
    double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0 );
    void drawSquares( cv::Mat& image, const std::vector<std::vector<cv::Point> >& squares );
    void vectorize(cv::Mat& img);

    cv::Point2f computeIntersect(cv::Vec2f line1, cv::Vec2f line2);
    std::vector<cv::Point2f> lineToPointPair(cv::Vec2f line);
    bool acceptLinePair(cv::Vec2f line1, cv::Vec2f line2, float minTheta);
    void detect(cv::Mat& occludedSquare);
    int run();
    //int hash(std::string line);

private:
    neuralNetwork* nn;
    //std::vector<std::string>* hashtbl;
};

#endif // DMFUNCTIONS_H
