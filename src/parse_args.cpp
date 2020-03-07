#include "parse_args.h"

parse_args::parse_args(int argc, char * argv[])
{
    char* filename = getCmdOption(argv, argv + argc, "-f");
    char* camera = getCmdOption(argv, argv + argc, "-c");
    char* needHelp = getCmdOption(argv, argv + argc, "-h");

    if (needHelp != nullptr)
    {
        mNeedHelp = true;
        return;
    }
    else if (filename != nullptr)
    {
        mFilename = std::string(filename);
    }
    else if (camera != nullptr)
    {
        int camNumber = -1;
        if (sscanf_s(camera, "%d", &camNumber) == 1 && camNumber != -1)
        {
            mCameraNum = camNumber;
        }
    }
    else
    {
        printf("No parameters were presented\n");
        mNeedHelp = true;
    }
}

char * parse_args::getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return nullptr;
}

void parse_args::printHelp()
{
    printf("Usage:\n");
    printf("laser_detect -f <path-to-video-file>      - To detect laser in video\n");
    printf("laser_detect -c <index-of-camera>         - To detect laser in stream from camera\n");
    printf("laser_detect -h                           - To see this help\n");
}
