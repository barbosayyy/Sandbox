#pragma once

#include "Shader.h"
#include "Texture.h"
namespace Sb {
    class Cubemap {
    public:
        Shader* _cubemapShader;
        u32 _textureFaceRightManifestID;
        u32 _textureFaceLeftManifestID;
        u32 _textureFaceTopManifestID;
        u32 _textureFaceBottomManifestID;
        u32 _textureFaceFrontManifestID;
        u32 _textureFaceBackManifestID;
        u32 data;
        u32 vertexData;
        void Draw();
    private:
    };
}