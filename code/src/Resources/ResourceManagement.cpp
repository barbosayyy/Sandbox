#include "ResourceManagement.h"
#include "ResourceManager.h"

namespace Sb {
    namespace ResourceManagement {
        String GetFullRelativePath(const String& assetPath) {
            return std::string("resources/") + std::string(assetPath);
        }

        Model* LoadModel(const String& assetPath) {
            ResourceManagement::ResourceManager& resManager = ResourceManagement::ResourceManager::GetInstance();
        
            return resManager.LoadModel(GetFullRelativePath(assetPath));
        }

        Model* LoadModel(Primitive primitive) {
            ResourceManagement::ResourceManager& resManager = ResourceManagement::ResourceManager::GetInstance();
        
            return resManager.LoadModel(primitive);
        }
        
        Texture* LoadTexture(const String& assetPath, TextureType type) { 
            ResourceManagement::ResourceManager& resManager = ResourceManagement::ResourceManager::GetInstance();
            
            return resManager.LoadTexture(GetFullRelativePath(assetPath), type);
        }
        Shader* LoadShader(const String& vertexShaderAssetPath, const String& fragmentShaderAssetPath) {
            ResourceManagement::ResourceManager& resManager = ResourceManagement::ResourceManager::GetInstance();
            
            return resManager.LoadShader(GetFullRelativePath(vertexShaderAssetPath), GetFullRelativePath(fragmentShaderAssetPath));
        }

        Cubemap* LoadCubemap(const String& rightTextureAssetPath, const String& leftTextureAssetPath, const String& topTextureAssetPath, const String& bottomTextureAssetPath, const String& frontTextureAssetPath, const String& backTextureAssetPath) {
            ResourceManagement::ResourceManager& resManager = ResourceManagement::ResourceManager::GetInstance();
            
            return resManager.LoadCubemap(GetFullRelativePath(rightTextureAssetPath), GetFullRelativePath(leftTextureAssetPath), GetFullRelativePath(topTextureAssetPath), GetFullRelativePath(bottomTextureAssetPath), GetFullRelativePath(frontTextureAssetPath), GetFullRelativePath(backTextureAssetPath));
        }
    }
}