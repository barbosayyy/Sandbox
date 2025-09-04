#pragma once 

#include "Core/Types.h"
#include "Rendering/Texture.h"
#include "Rendering/Shader.h"

namespace Sb {
    class NewMaterial {
    public:
        Color _color {1.0f, 1.0f, 1.0f, 1.0f};
        Shader* _shader;
        std::vector<Texture> _diffuseMap;
        std::vector<Texture> _specularMap;
        std::vector<Texture> _normalMap;
        std::vector<Texture> _emissionMap;

        float _normal {1.0f};
        float _metallic {0.0f};
        float _roughness {0.0f};
        float _emission {0.0f};

        // GPU flags

        // u8 sbMaterialGpuFlags;
    };
}