#pragma once
#include <vector>
#include "Shader.h"

namespace Sandbox{
    struct Material{
        std::vector<unsigned int> _texture;
        std::vector<Shader*> _shaders;
        Shader* _shader;
    };
}