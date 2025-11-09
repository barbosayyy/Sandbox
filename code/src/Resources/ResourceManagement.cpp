#include "ResourceManagement.h"
#include "ResourceManager.h"

namespace Sb {
    namespace ResourceManagement {
        Model* LoadModel(const String& assetPath) {
            ResourceManagement::ResourceManager& resManager = ResourceManagement::ResourceManager::GetInstance();
        
            return resManager.LoadModel(assetPath);
        }

        Model* LoadModel(Primitive primitive) {
            ResourceManagement::ResourceManager& resManager = ResourceManagement::ResourceManager::GetInstance();
        
            return resManager.LoadModel(primitive);
        }

        Model* LoadModel(const String& assetPath) {
            ResourceManagement::ResourceManager& resManager = ResourceManagement::ResourceManager::GetInstance();
        
            return resManager.LoadModel(assetPath);
        }
        
        Texture* LoadTexture(const String& assetPath, TextureType type) { 
            ResourceManagement::ResourceManager& resManager = ResourceManagement::ResourceManager::GetInstance();
            
            return resManager.LoadTexture(assetPath, type);
        }
        Shader* LoadShader(const String& vertexShaderAssetPath, const String& fragmentShaderAssetPath) {
            ResourceManagement::ResourceManager& resManager = ResourceManagement::ResourceManager::GetInstance();
            
            return resManager.LoadShader(vertexShaderAssetPath, fragmentShaderAssetPath);
        }

        Cubemap* LoadCubemap(const String& rightTextureAssetPath, const String& leftTextureAssetPath, const String& topTextureAssetPath, const String& bottomTextureAssetPath, const String& frontTextureAssetPath, const String& backTextureAssetPath) {
            ResourceManagement::ResourceManager& resManager = ResourceManagement::ResourceManager::GetInstance();
            
            return resManager.LoadCubemap(rightTextureAssetPath, leftTextureAssetPath, topTextureAssetPath, bottomTextureAssetPath, frontTextureAssetPath, backTextureAssetPath);
        }
    }
}