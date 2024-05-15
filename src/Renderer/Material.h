#pragma once
#include <vector>
#include "Shader.h"
#include "../Core/Types.h"

namespace Sandbox{

    struct Material{
        std::vector<unsigned int> textures;
        std::vector<Shader*> shaders;
        float roughnessStrength;
        float emissiveStrength;
        vec4 colorOverlay;
    };
}