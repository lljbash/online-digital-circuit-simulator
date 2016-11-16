#pragma once

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "util/util.h"

class VcdParser {

    public:
        //static cv::Mat parse(std::string vcd_code);
        static std::string parse(std::string vcd_code);

};

