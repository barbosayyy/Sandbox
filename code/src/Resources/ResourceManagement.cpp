#include "ResourceManagement.h"
#include "ResourceManager.h"

namespace Sb {
    namespace ResourceManagement {
        Model* LoadModel(u32 assetID) {
            ResourceManagement::ResourceManager& resManager = ResourceManagement::ResourceManager::GetInstance();
        
            return resManager.LoadModel(assetID);
        }
        
        Texture* LoadTexture(u32 assetID, TextureType type) { 
            ResourceManagement::ResourceManager& resManager = ResourceManagement::ResourceManager::GetInstance();
            
            return resManager.LoadTexture(assetID, type);
        }
        Shader* LoadShader(u32 vertexManifestID, u32 fragmentManifestID) {
            ResourceManagement::ResourceManager& resManager = ResourceManagement::ResourceManager::GetInstance();
            
            return resManager.LoadShader(vertexManifestID, fragmentManifestID);
        }

        Cubemap* LoadCubemap(u32 rightTextureID, u32 leftTextureID, u32 topTextureID, u32 botTextureID, u32 frontTextureID, u32 backTextureID) {
            ResourceManagement::ResourceManager& resManager = ResourceManagement::ResourceManager::GetInstance();
            
            return resManager.LoadCubemap(rightTextureID, leftTextureID, topTextureID, botTextureID, frontTextureID, backTextureID);
        }
    }
}