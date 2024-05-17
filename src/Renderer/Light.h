#pragma once

#include "../Math/Vectors.h"

namespace Sandbox{
    struct Light {
        vec4 color;
        float intensity {0.5f};
    };

    using AmbientLight = Light;

    struct DirecctionalLight : Light{
        vec3 rotation;
    };

    struct PointLight : Light{
        vec3 position;
    };

    struct SpotLight : Light{
        vec3 position;
        vec3 rotation;
        float innerRadius;
        float outerRadius;
    };
}