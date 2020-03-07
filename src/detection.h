#pragma once
#include <string>

#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <memory>

#include "parse_args.h"

class detection {
public:
    detection() = default;
    virtual ~detection();
    detection(const parse_args& args);

    detection(detection&) = delete;
    detection& operator=(const detection&) = delete;

    void start();
    virtual void detect(const cv::Mat& input, cv::Mat& output) = 0;
    virtual void detect(cv::Mat& input) = 0;
    bool setCapture(const std::string& filename);
    bool setCapture(int camIndex);
    bool captureIsOpened();

    template<class T>
    static std::unique_ptr<T> createDetectionFromArgs(const parse_args& args)
    {
        return std::make_unique<T>(args);
    }

protected:
    void drawRect(cv::Mat& frame, cv::Rect2i rect);

protected:
    cv::Size mFrameSize;

private:
    std::string mWindowName = "Output";
    cv::VideoCapture mCapture;
};
