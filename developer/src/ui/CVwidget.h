//
// Created by cxfeng on 19-3-21.
//

#ifndef AIBONE_CVWIDGET_H
#define AIBONE_CVWIDGET_H
#include <opencv2/opencv.hpp>
#include "GLwidget.h"


class CVwidget{
public:
    CVwidget();
    ~CVwidget();

    void ReadFrame();

private:

    cv::VideoCapture capture;
    cv::Mat frame;
    cv::Mat result_frame;

};


#endif //AIBONE_CVWIDGET_H
