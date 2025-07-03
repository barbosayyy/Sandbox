#pragma once 

#include "Core/Base.h"


namespace SbEngine{
    constexpr s16 DEFAULT_WINDOW_WIDTH = 1920;
    constexpr s16 DEFAULT_WINDOW_HEIGHT = 1080;
    struct Config{
        Config();
        s16 windowWidth;
        s16 windowHeight;
    };
};
