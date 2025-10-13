#pragma once

#include "Rendering/Model.h"
#include "Rendering/Cubemap.h"

namespace Sb {
    namespace ResourceManagement {
        Model* LoadModel(u32 assetID);
        Texture* LoadTexture(u32 assetID, TextureType type);
        Shader* LoadShader(u32 vertexManifestID, u32 fragmentManifestID);
        Cubemap* LoadCubemap(u32 rightTextureID, u32 leftTextureID, u32 topTextureID, u32 botTextureID, u32 frontTextureID, u32 backTextureID);
    }
}
