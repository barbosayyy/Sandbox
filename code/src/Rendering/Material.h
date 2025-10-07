#pragma once 

#include "Core/Types.h"
#include "Rendering/Texture.h"
#include "Rendering/Shader.h"

namespace Sb {
    class Material {
    public:
        Color _color {1.0f, 1.0f, 1.0f, 1.0f};
        Shader* _shader;
        Texture _diffuseMap;
        Texture _specularMap;
        Texture _normalMap;
        Texture _emissionMap;

        float _normal {1.0f};
        float _metallic {0.0f};
        float _roughness {0.0f};
        float _emission {0.0f};

        // GPU flags

        // u8 sbMaterialGpuFlags;
    };
}