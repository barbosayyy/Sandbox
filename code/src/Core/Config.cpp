#include "Config.h"

using namespace SbEngine;

Config::Config(){

    // Debug (force) or no configuration file found
    #ifdef SB_DEBUG
        windowWidth = DEFAULT_WINDOW_WIDTH;
        windowHeight = DEFAULT_WINDOW_HEIGHT;
    #endif
}