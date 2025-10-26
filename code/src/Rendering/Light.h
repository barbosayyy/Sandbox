#pragma once

#include "Core/Config.h"
#include "Math/Vectors.h"

namespace Sb {
    enum class LightType : int {
        Point = 0,
        Spot = 1,
        Directional = 2,
        Ambient = 3,
        Rect = 4
    };

    //Sandbox Engine's Light base primitive data type
    struct Light {
        vec3 color {1};
        float intensity {1};
        LightType type {0};
        float range {1};
    };

    // std140 - must be aligned to 16 bytes
    struct LightUBO {
        alignas(16)vec3 position;  
        alignas(16)vec3 color;
        alignas(4)int type;
        alignas(4)float linear;
        alignas(4)float quadratic;
        alignas(4)float intensity;
        alignas(4)float radius;
    };

    // GL_MAX_UNIFORM_BLOCK_SIZE = 16384
    struct alignas(16) LightUBOData {
        LightUBO lights[SB_RENDERER_MAX_NUM_LIGHTS];
        u32 numLights;
    };
}