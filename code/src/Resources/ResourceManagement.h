#pragma once

#include "Core/Types.h"
#include "Rendering/Model.h"
#include "Rendering/Cubemap.h"

namespace Sb {
    namespace ResourceManagement {
        using Primitive = DefaultMesh;

        Model* LoadModel(const String& assetPath);
        Model* LoadModel(Primitive primitive);
        Texture* LoadTexture(const String& assetPath, TextureType type);
        Shader* LoadShader(const String& vertexShaderAssetPath, const String& fragmentShaderAssetPath);
        Cubemap* LoadCubemap(const String& rightTextureAssetPath, const String& leftTextureAssetPath, const String& topTextureAssetPath, const String& bottomTextureAssetPath, const String& frontTextureAssetPath, const String& backTextureAssetPath);
    }
}
