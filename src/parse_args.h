#pragma once
#include <string>
#include <vector>

class parse_args
{
public:
    parse_args(int argc, char* argv[]);

    struct arg {
        std::string key;
        std::string value;

        arg(const std::string& key, const std::string& value)
            : key(key)
            , value(value)
        {}
    };

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