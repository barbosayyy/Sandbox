#pragma once

#include "Core/Types.h"
#include "Core/Singleton.h"
#include "ECS/Components.h"

#include "Rendering/Model.h"
#include "Rendering/Shader.h"

#include <functional>
#include <unordered_map>
namespace Sb {

    namespace ResourceManagement {

        // Necessary for looking up both shader sources
        struct ShaderManifestID {
            u32 vertexManifestID;
            u32 fragmentManifestID;
            bool operator==(const ShaderManifestID& other) const {
                return vertexManifestID == other.vertexManifestID && fragmentManifestID == other.fragmentManifestID;
            }
        };

        // ShaderManifestID type map hasher
        struct ShaderManifestIDHash {
            size_t operator()(const ShaderManifestID& other) const noexcept {
                return std::hash<u32>()(other.vertexManifestID) ^ (std::hash<u32>()(other.fragmentManifestID) << 1);
            }
        };

        // Cache data types
            struct CacheData {
                u32 refCount;
            };

            struct ModelCacheData : CacheData {
                Model model;
            };

            struct TextureCacheData : CacheData {
                Texture texture;
            };

            struct ShaderCacheData : CacheData {
                Shader shader;
            };

        enum class ResourceID{
            // Shaders -> 0-15
            SHADER_FRAGMENT = 0,
            SHADER_VERTEX = 1,
    
            // Textures -> 16-31
            TEXTURE_JPG = 16,
            TEXTURE_PNG = 17
        };
    
        // TODO: This could be improved in the future
        class ResourceManager : public Singleton<ResourceManager, int>{
        public:
            ResourceManager();
            
            Model* LoadModel(u32 manifestID);
            Texture* LoadTexture(u32 manifestID, TextureType type);
            Shader* LoadShader(u32 vertexManifestID, u32 fragmentManifestID);

            void UnloadModel(u32 manifestID);
            void UnloadTexture(u32 manifestID);
            void UnloadShader(ShaderManifestID shaderManifestID);
            void UnloadShader(u32 vertexManifestID, u32 fragmentManifestID);
            
            // 
                String GetYamlResourceNameFromResourceID(ResourceID rId);
                Resource GetDataFromID(ResourceID rId, int id);

        private:
            std::unordered_map<u32, ModelCacheData> _modelCache;
            std::unordered_map<u32, TextureCacheData> _textureCache;
            std::unordered_map<ShaderManifestID, ShaderCacheData, ShaderManifestIDHash> _shaderCache;
            u32 _faceCount;
            YAML::Node _manifestAssetsNode;
        };
    }
}