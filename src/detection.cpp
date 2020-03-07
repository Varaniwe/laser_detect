#include "detection.h"
#include <iostream>
#include "opencv2/highgui.hpp"

static constexpr int KEY_ESC = 27;

detection::~detection()
{
    cv::destroyWindow(mWindowName);
}

detection::detection(const parse_args & args)
{
    if (args.needHelp())
    {
        return;
    }

    if (args.cameraNum() != parse_args::kCamIsNotPresented)
    {
        setCapture(args.cameraNum());
    }
    else if (!args.filename().empty())
    {
        setCapture(args.filename());
    }
}

void detection::start()
{
    if (!mCapture.isOpened())
    {
        printf("Cannot create capture\n");
        return;
    }

    cv::namedWindow(mWindowName, cv::WINDOW_NORMAL);

    const double fps = mCapture.get(cv::CAP_PROP_FPS);
    const int interval = fps > 0.1 ? static_cast<int>(1000.0 / fps) : 33;

    mFrameSize = cv::Size(static_cast<int>(mCapture.get(cv::CAP_PROP_FRAME_WIDTH)),
        static_cast<int>(mCapture.get(cv::CAP_PROP_FRAME_HEIGHT)));

    printf("Frame size: %d x %d, Frame interval: %d (FPS - %f)\n", mFrameSize.width, mFrameSize.height, interval, fps);

    cv::Mat frame;
    while (mCapture.read(frame))
    {
        detect(frame);

        char c = cv::waitKey(interval);
        if (c == KEY_ESC)
        {
            break;
        }

        cv::imshow(mWindowName, frame);
    }
}

void detection::setCapture(const std::string & filename)
{
    mCapture.open(filename, cv::CAP_ANY);
}

void detection::setCapture(int camIndex)
{
    mCapture.open(camIndex, cv::CAP_ANY);
}

bool detection::captureIsOpened()
{
    return mCapture.isOpened();
}

void detection::drawRect(cv::Mat& frame, cv::Rect2i rect)
{
    /*
    2--------3
    |        |
    1--------4
    */
    auto point1 = cv::Point2i(rect.x, rect.y + rect.height);
    auto point2 = cv::Point2i(rect.x, rect.y);
    auto point3 = cv::Point2i(rect.x + rect.width, rect.y);
    auto point4 = cv::Point2i(rect.x + rect.width, rect.y + rect.height);

    const cv::Scalar color = frame.channels() > 1 ? cv::Scalar{ 0, 255, 0 } : cv::Scalar{ 255, 255, 255 };
    int thickness = 1;
    int radius = 20;
    cv::line(frame, { point1.x - radius, point1.y + radius }, { point2.x - radius, point2.y - radius }, color, thickness);
    cv::line(frame, { point2.x - radius, point2.y - radius }, { point3.x + radius, point3.y - radius }, color, thickness);
    cv::line(frame, { point4.x + radius, point4.y + radius }, { point3.x + radius, point3.y - radius }, color, thickness);
    cv::line(frame, { point1.x - radius, point1.y + radius }, { point4.x + radius, point4.y + radius }, color, thickness);
}
