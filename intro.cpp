//
// Created by nes on 2024/2/26.
//

#include "1-start/3-triangle/triangle.h"
#include "1-start/4-shaders/timed-triangle.h"
#include "common/log.h"

int main()
{
    log("main start...");

    // helloWindow();
    // Triangle::run();
    TimedTriangle::run();

    log("main end...");
    return 0;
}
