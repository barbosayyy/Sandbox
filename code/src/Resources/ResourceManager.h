#pragma once

#include "Core/Types.h"
#include "Core/Singleton.h"

#include "Rendering/Model.h"
#include "Rendering/Shader.h"
#include "Rendering/Cubemap.h"

#include <functional>
#include <unordered_map>
namespace Sb {

    namespace ResourceManagement {

        struct AssetMetadata {
            String name;
            String path;
        };

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

            struct CubemapManifestID {
                u32 rightTextureManifestID;
                u32 leftTextureManifestID;
                u32 topTextureManifestID;
                u32 bottomTextureManifestID;
                u32 frontTextureManifestID;
                u32 backTextureManifestID;

                bool operator==(const CubemapManifestID& other) const {
                    return rightTextureManifestID == other.rightTextureManifestID &&
                     leftTextureManifestID == other.leftTextureManifestID &&
                     topTextureManifestID == other.topTextureManifestID &&
                     bottomTextureManifestID == other.bottomTextureManifestID &&
                     frontTextureManifestID == other.frontTextureManifestID &&
                     backTextureManifestID == other.backTextureManifestID;
                }
            };

            // ShaderManifestID type map hasher
            struct CubemapManifestIDHash {
                size_t operator()(const CubemapManifestID& other) const noexcept {
                    std::size_t h = 0;
                    auto combine = [&h](u32 v) {
                        // hash combine
                        h ^= std::hash<u32>{}(v) + 0x9e3779b9 + (h << 6) + (h >> 2);
                    };
                    combine(other.rightTextureManifestID);
                    combine(other.leftTextureManifestID);
                    combine(other.topTextureManifestID);
                    combine(other.bottomTextureManifestID);
                    combine(other.frontTextureManifestID);
                    combine(other.backTextureManifestID);
                    return h;
                }
            };

            struct CubemapCacheData : CacheData {
                Cubemap cubemap;
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
            
            std::unordered_map<u32, AssetMetadata> const& GetAssetMetadata() { return _assetMetadataCache; };

            Model* LoadModel(u32 manifestID);
            Texture* LoadTexture(u32 manifestID, TextureType type);
            Shader* LoadShader(u32 vertexManifestID, u32 fragmentManifestID);
            Cubemap* LoadCubemap(u32 rightTextureID, u32 leftTextureID, u32 topTextureID, u32 botTextureID, u32 frontTextureID, u32 backTextureID);
            
            void UnloadModel(u32 manifestID);
            void UnloadTexture(u32 manifestID);
            void UnloadShader(ShaderManifestID shaderManifestID);
            void UnloadShader(u32 vertexManifestID, u32 fragmentManifestID);
            void UnloadCubemap(Cubemap* cubemap);
            
            // 
                String GetYamlResourceNameFromResourceID(ResourceID rId);
                Resource GetDataFromID(ResourceID rId, int id);

        private:
            std::unordered_map<u32, ModelCacheData> _modelCache;
            std::unordered_map<u32, TextureCacheData> _textureCache;
            std::unordered_map<ShaderManifestID, ShaderCacheData, ShaderManifestIDHash> _shaderCache;
            std::unordered_map<CubemapManifestID, CubemapCacheData, CubemapManifestIDHash> _cubemapCache;

            std::unordered_map<u32, AssetMetadata> _assetMetadataCache;
            
            u32 _faceCount;
        
            bool LoadMetadata(u32 targetLoadPtr);
            u32 _loadedMetadataChunkIndex;
            u32 manifestSize;
        };
    }
}