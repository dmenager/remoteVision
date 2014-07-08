#ifndef UBYTEEXTRACTOR_H
#define UBYTEEXTRACTOR_H

#include <string>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <vector>
#include <byteswap.h>
#include <arpa/inet.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>

#include "radonTransformer.h"

class UbyteExtractor
{
    public:
          UbyteExtractor();
          virtual ~UbyteExtractor();
          void convert();
    private:
          std::vector<std::vector<pixel> > build(std::fstream& fin, std::fstream& fin2, std::ofstream& fout, std::ofstream& log);

};

#endif // UBYTEEXTRACTOR_H
