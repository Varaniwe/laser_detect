#include <iostream>
#include "src/hsv_detection.h"
#include "src/parse_args.h"

int main(int argc, char* argv[])
{
    parse_args pa(argc, argv);

    if (pa.needHelp())
    {
        pa.printHelp();
        return 0;
    }

    auto hsvDetection = detection::createDetectionFromArgs<hsv_detection>(pa);
    if (!hsvDetection || !hsvDetection->captureIsOpened())
    {
        pa.printHelp();
        return -1;
    }

    hsvDetection->start();
    return 0;
}