#pragma once
#include <string>
#include <vector>

class parse_args
{
public:
    parse_args(int argc, char* argv[]);

    void printHelp();
    bool needHelp() const { return mNeedHelp; }
    int cameraNum() const { return mCameraNum; }
    std::string filename() const { return mFilename; }

    static constexpr int kCamIsNotPresented = -1;

private:
    char* getCmdOption(char ** begin, char ** end, const std::string & option);

private:
    std::string mFilename;
    int mCameraNum = kCamIsNotPresented;
    bool mNeedHelp = false;
};