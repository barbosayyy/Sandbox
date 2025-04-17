#pragma once

#include "Shader.h"
#include "Core/Types.h"
#include "Texture.h"

#include <vector>

namespace SbEngine{
    constexpr u16 SB_MAT_TEX            = 1 << 0;
    constexpr u16 SB_MAT_LIT            = 1 << 1;
    constexpr u16 SB_MAT_COLOVERLAY     = 1 << 2;
    constexpr u16 SB_MAT_EMISS          = 1 << 3;

    struct Material{

        Material();
        std::vector<Texture> textures;
        std::vector<Shader*> shaders;
        float roughnessStrength;
        float emissiveStrength;
        vec4 colorOverlay;
        u16 flags;

        void SetEm(float param) {emissiveStrength = param;};
        void SetRough(float param) {roughnessStrength = param;};

        void AddTexture(const Texture& tex);

        void SetColorOverlay(const vec4& color);

        void AddFlag(u16 flag);
        void RemoveFlag(u16 flag);
    };
}