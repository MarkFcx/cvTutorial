//
// Created by cxfeng on 19-3-21.
//
#include "ui_GLwidget.h"
#include <QtGui/QImage>
#include "CVwidget.h"

void CVwidget::ReadFrame()
{
    if(capture.isOpened())
    {
        capture >> frame;
        if(!frame.empty())
        {
            cvtColor(frame, result_frame, CV_BGR2RGB);
            cv::resize(result_frame, result_frame, cv::Size(640, 480));

        }
    }

}
