#pragma once

#include "Scene.h"

#include <vector>

namespace SbEngine{
    class SceneManager{
        
    private:
        std::vector<Scene> _scenes;
    };
}