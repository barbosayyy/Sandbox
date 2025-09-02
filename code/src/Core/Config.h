#pragma once 

#include "Core/Base.h"

namespace Sb {
    constexpr u16 DEFAULT_WINDOW_WIDTH = 1920;
    constexpr u16 DEFAULT_WINDOW_HEIGHT = 1080;
    constexpr u16 DEFAULT_VIEWPORT_WIDTH = DEFAULT_WINDOW_WIDTH;
    constexpr u16 DEFAULT_VIEWPORT_HEIGHT = DEFAULT_WINDOW_HEIGHT;
    constexpr s16 DEFAULT_VIEWPORT_X = 0;
    constexpr s16 DEFAULT_VIEWPORT_Y = 0;

    struct Config{
        Config();
        s16 windowWidth;
        s16 windowHeight;
    };
};
