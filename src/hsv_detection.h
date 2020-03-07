#pragma once
#include "detection.h"

// Based on lesson http://robocraft.ru/blog/computervision/402.html

class hsv_detection : public detection
{
public:
    hsv_detection() = default;
    ~hsv_detection() = default;

    hsv_detection(const parse_args& args);

    void detect(const cv::Mat& input, cv::Mat& output) override;
    void detect(cv::Mat& input) override;

    // TODO: add mechanism to calibrate parameters
    static constexpr int kOptimalHmin = 159;
    static constexpr int kOptimalHmax = 179;
    static constexpr int kOptimalSmin = 1;
    static constexpr int kOptimalSmax = 255;
    static constexpr int kOptimalVmin = 165;
    static constexpr int kOptimalVmax = 200;

private:
    void initPlanes(const cv::Mat& frame);
    void highlightPointer(const cv::Mat& frame, cv::Mat& outFrame);
    bool findCountours(const cv::Mat& frame, cv::Rect2i& outRect);

private:
    struct HsvImagePlanes {
        HsvImagePlanes(cv::Size size)
        {
            h = cv::Mat(size, CV_8UC1);
            s = cv::Mat(size, CV_8UC1);
            v = cv::Mat(size, CV_8UC1);
        }

        cv::Mat h;
        cv::Mat s;
        cv::Mat v;
    };

    HsvImagePlanes mHsvPlanes = HsvImagePlanes({ 0, 0 });
    HsvImagePlanes mHsvRanges = HsvImagePlanes({ 0, 0 });
    cv::Mat mHsvAnd;
};