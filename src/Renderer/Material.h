#pragma once
#include <vector>
#include "Shader.h"
#include "../Core/Types.h"
#include "Texture.h"

namespace Sandbox{

    struct Material{
        std::vector<Texture> textures;
        std::vector<Shader*> shaders;
        float roughnessStrength;
        float emissiveStrength;
        vec4 colorOverlay;
    };
}