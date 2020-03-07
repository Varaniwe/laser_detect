#include "hsv_detection.h"

#include <opencv2/imgproc/types_c.h>

hsv_detection::hsv_detection(const parse_args& args)
    : detection(args)
{}

void hsv_detection::detect(const cv::Mat& input, cv::Mat& output)
{
    input.copyTo(output);
    detect(output);
}

void hsv_detection::detect(cv::Mat& input)
{
    initPlanes(input);

    highlightPointer(input, mHsvAnd);

    cv::Rect2i rect;
    if (findCountours(mHsvAnd, rect))
    {
        drawRect(input, rect);
    }
}

void hsv_detection::initPlanes(const cv::Mat& frame)
{
    if (mHsvPlanes.h.rows != 0 || mHsvPlanes.h.cols != 0 ||
        mHsvPlanes.s.rows != 0 || mHsvPlanes.s.cols != 0 ||
        mHsvPlanes.v.rows != 0 || mHsvPlanes.v.cols != 0)
    {
        return;
    }

    mHsvPlanes = HsvImagePlanes(mFrameSize);
    mHsvRanges = HsvImagePlanes(mFrameSize);
    mHsvAnd = cv::Mat(mFrameSize, CV_8UC1);
}

void hsv_detection::highlightPointer(const cv::Mat& frame, cv::Mat& outFrame)
{
    cv::cvtColor(frame, outFrame, CV_BGR2HSV);

    std::vector<cv::Mat> hsv_channels = { mHsvPlanes.h, mHsvPlanes.s, mHsvPlanes.v };
    cv::split(outFrame, hsv_channels);

    cv::inRange(mHsvPlanes.h, cv::Scalar(kOptimalHmin), cv::Scalar(kOptimalHmax), mHsvRanges.h);
    cv::inRange(mHsvPlanes.s, cv::Scalar(kOptimalSmin), cv::Scalar(kOptimalSmax), mHsvRanges.s);
    cv::inRange(mHsvPlanes.v, cv::Scalar(kOptimalVmin), cv::Scalar(kOptimalVmax), mHsvRanges.v);

    cv::bitwise_and(mHsvRanges.h, mHsvRanges.s, outFrame);
    cv::bitwise_and(outFrame, mHsvRanges.v, outFrame);
}

bool hsv_detection::findCountours(const cv::Mat& frame, cv::Rect2i& outRect)
{
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(frame, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

    double largestArea = -1.0;
    size_t largestContourIndex = -1;
    for (size_t i = 0; i < contours.size(); i++)
    {
        double d = cv::contourArea(contours[i], false);

        if (d > largestArea) {
            largestArea = d;
            largestContourIndex = i;
        }
    }

    static cv::Rect2i previousRect = cv::Rect2i();
    if (!contours.empty() && largestContourIndex != -1) {
        auto pointerRect = cv::minAreaRect(contours[largestContourIndex]);
        std::vector<cv::Point2f> boxPoints(4);
        pointerRect.points(boxPoints.data());
        previousRect = cv::Rect2i(cv::Point2i(boxPoints[0]), cv::Point2i(boxPoints[3]));
    }

    outRect = previousRect;
    return largestContourIndex != -1;
}