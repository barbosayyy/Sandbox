#pragma once

#include "Core/Types.h"
#include "Core/Crypto.h"
#include "Core/Singleton.h"

#include "Rendering/Model.h"
#include "Rendering/Shader.h"
#include "Rendering/Cubemap.h"

#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>
namespace Sb {

    namespace ResourceManagement {

        struct AssetMetadata {
            String name;
            String path;
        };

        // Necessary for looking up both shader sources
        struct ShaderManifestID {
            SbGUID vertexManifestID;
            SbGUID fragmentManifestID;
            bool operator==(const ShaderManifestID& other) const {
                return vertexManifestID == other.vertexManifestID && fragmentManifestID == other.fragmentManifestID;
            }
        };

        // ShaderManifestID type map hasher
        struct ShaderManifestIDHash {
            size_t operator()(const ShaderManifestID& other) const noexcept {
                size_t h = 0;
                Crypto::HashCombine(h, other.vertexManifestID);
                Crypto::HashCombine(h, other.fragmentManifestID);
                return h;
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
                SbGUID rightTextureManifestID;
                SbGUID leftTextureManifestID;
                SbGUID topTextureManifestID;
                SbGUID bottomTextureManifestID;
                SbGUID frontTextureManifestID;
                SbGUID backTextureManifestID;

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
                    size_t h = 0;
                    Crypto::HashCombine<SbGUID>(h, other.rightTextureManifestID);
                    Crypto::HashCombine<SbGUID>(h, other.leftTextureManifestID);
                    Crypto::HashCombine<SbGUID>(h, other.topTextureManifestID);
                    Crypto::HashCombine<SbGUID>(h, other.bottomTextureManifestID);
                    Crypto::HashCombine<SbGUID>(h, other.frontTextureManifestID);
                    Crypto::HashCombine<SbGUID>(h, other.backTextureManifestID);
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

            Model* LoadModel(const String& assetPath);
            Model* LoadModel(DefaultMesh primitive);
            Texture* LoadTexture(const String& assetPath, TextureType type);
            Shader* LoadShader(const String& vertexShaderAssetPath, const String& fragmentShaderAssetPath);
            Cubemap* LoadCubemap(const String& rightTextureAssetPath, const String& leftTextureAssetPath,
                const String& topTextureAssetPath, const String& bottomTextureAssetPath,
                const String& frontTextureAssetPath, const String& backTextureAssetPath);
            
            void UnloadModel(SbGUID assetGUID);
            void UnloadTexture(SbGUID assetGUID);
            void UnloadShader(ShaderManifestID assetGUID);
            void UnloadCubemap(CubemapManifestID assetGUID);
            
            //
                String GetYamlResourceNameFromResourceID(ResourceID rId);
                Resource GetDataFromID(ResourceID rId, int id);

            SbGUID GetSbGUIDFromU32Hash(u32 pathHash) {
                SbGUID guid {};
                if(_pathHashToGUID.count(pathHash) > 0) {
                    guid.h1 = _pathHashToGUID[pathHash].h1;
                    guid.h2 = _pathHashToGUID[pathHash].h2;
                }
                return guid;
            }

        private:
            SbGUID GetGUIDByAssetPath(const String& assetPath);

            std::unordered_map<SbGUID, ModelCacheData> _modelCache;
            std::unordered_map<SbGUID, TextureCacheData> _textureCache;
            std::unordered_map<ShaderManifestID, ShaderCacheData, ShaderManifestIDHash> _shaderCache;
            std::unordered_map<CubemapManifestID, CubemapCacheData, CubemapManifestIDHash> _cubemapCache;

            std::unordered_map<SbGUID, u32> _guidToAssetPathIndex;
            std::unordered_map<u32, SbGUID> _pathHashToGUID;
            std::vector<std::string> _assetPaths;

            u32 _faceCount;
            
            void LoadPrimitiveMetadata();
            
            bool LoadCommonMetadata();
            bool LoadResourceMetadata();
            u32 _loadedMetadataChunkIndex;
            u32 manifestSize;
        };
    }
}