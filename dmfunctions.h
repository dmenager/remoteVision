#ifndef DMFUNCTIONS_H
#define DMFUNCTIONS_H

#include <alvision/alvisiondefinitions.h>
#include <alvalue/alvalue.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class DMFunctions
{
public:
    DMFunctions();
    void DisplayVid(AL::ALValue& vPtr);
private:
    void locateObj();
};

#endif // DMFUNCTIONS_H
