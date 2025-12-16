#include "Core/Base.h"
#include "Core/Config.h"
#include "Core/Types.h"
#include "Core/Crypto.h"
#include "Core/Utils.h"
#include "Core/Debug.h"
#include "ResourceManager.h"

#include "Rendering/OpenGL/GLBuffer.h"
#include "ResourceManifest.h"
#include "ResourceManager.h"
#include "Primitive.h"
#include "DefaultPrimitives.h"

#include "Resources/ResourceManagement.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include <cstdlib>
#include <filesystem>
#include <smhasher/MurmurHash3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include "yaml-cpp/yaml.h"

namespace Sb {
    namespace ResourceManagement {
        
#ifdef SB_BUILD_DEBUG
        // #define SB_BUILD_DEBUG_RESOURCE_MANAGEMENT
        // #define SB_BUILD_DEBUG_ASSIMP
#endif
        // Textures
        Texture LoadTextureResource(const String& path, TextureType type, GLint wrapMethod, bool flipVertical, bool gammaCorrection);
        u32 LoadCubemapTexture(const String& rightTextureAssetPath, const String& leftTextureAssetPath, const String& topTextureAssetPath, const String& bottomTextureAssetPath, const String& frontTextureAssetPath, const String& backTextureAssetPath);
        
        // Assimp (OBJ)
        void AssimpProcessNode(aiNode* node, const aiScene *scene, const String& path, Model& model, std::vector<Texture>& loadedTextures);
        std::vector<Texture> AssimpLoadMaterialTextures(aiMaterial* mat, aiTextureType type, const String& path, std::vector<Texture>& loadedTextures);
        Mesh AssimpProcessMesh(aiMesh* mesh, const aiScene* scene, const String& path, std::vector<Texture>& loadedTextures);

        // Texture load Utils
            Texture LoadTextureResource(const String& path, TextureType type, GLint wrapMethod, bool flipVertical, bool gammaCorrection) {
                Texture texture;

                texture.name = std::string(path).substr(std::string(path).find_last_of("\\")+1, std::string(path).size());

                glGenTextures(1, &texture.id);

                stbi_set_flip_vertically_on_load(flipVertical);
		        unsigned char* data = stbi_load(path.c_str(), &texture.width, &texture.height, &texture.numChannels, 0);

                if (data) {
                    GLenum format;
                    if(texture.numChannels == 1)
                        format = GL_RED;
                    else if(texture.numChannels == 3)
                        format = GL_RGB;
                    else if(texture.numChannels == 4)
                        format = GL_RGBA;
                    glBindTexture(GL_TEXTURE_2D, texture.id);
                    glTexImage2D(GL_TEXTURE_2D, 0, format, texture.width, texture.height, 0, format, GL_UNSIGNED_BYTE, data);
                    glGenerateMipmap(GL_TEXTURE_2D);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMethod);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMethod);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                }
                else {
                    texture.id = 0;
                    Log::Error("Texture: Failed to load texture from: ", path);
                }
                
                stbi_image_free(data);

                return texture;
            }

            u32 LoadCubemapTexture(const String& rightTextureAssetPath, const String& leftTextureAssetPath, const String& topTextureAssetPath, const String& bottomTextureAssetPath, const String& frontTextureAssetPath, const String& backTextureAssetPath) {
                u32 cubemapData;
                
                glGenTextures(1, &cubemapData);
                glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapData);
                stbi_set_flip_vertically_on_load(false);
                
                ResourceManager& res = ResourceManager::GetInstance();
                unsigned char* data;
                int width, height, nChannels;
                data = stbi_load(rightTextureAssetPath, &width, &height, &nChannels, 0);
                if(data){
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+0, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    stbi_image_free(data);
                    Log::Info("ResourceManager: Loaded cubemap face: ", rightTextureAssetPath);
                }
                else{
                    std::cout << "err texture" << std::endl;
                    stbi_image_free(data);
                }
                data = stbi_load(leftTextureAssetPath, &width, &height, &nChannels, 0);
                if(data){
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+1, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    stbi_image_free(data);
                    Log::Info("ResourceManager: Loaded cubemap face: ", leftTextureAssetPath);
                }
                else{
                    std::cout << "err texture" << std::endl;
                    stbi_image_free(data);
                }
                data = stbi_load(topTextureAssetPath, &width, &height, &nChannels, 0);
                if(data){
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+2, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    stbi_image_free(data);
                    Log::Info("ResourceManager: Loaded cubemap face: ", topTextureAssetPath);
                }
                else{
                    std::cout << "err texture" << std::endl;
                    stbi_image_free(data);
                }
                data = stbi_load(bottomTextureAssetPath, &width, &height, &nChannels, 0);
                if(data){
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+3, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    stbi_image_free(data);
                    Log::Info("ResourceManager: Loaded cubemap face: ", bottomTextureAssetPath);
                }
                else{
                    std::cout << "err texture" << std::endl;
                    stbi_image_free(data);
                }
                data = stbi_load(frontTextureAssetPath, &width, &height, &nChannels, 0);
                if(data){
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+4, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    stbi_image_free(data);
                    Log::Info("ResourceManager: Loaded cubemap face: ", frontTextureAssetPath);
                }
                else{
                    std::cout << "err texture" << std::endl;
                    stbi_image_free(data);
                }
                data = stbi_load(backTextureAssetPath, &width, &height, &nChannels, 0);
                if(data){
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+5, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    stbi_image_free(data);
                    Log::Info("ResourceManager: Loaded cubemap face: ", backTextureAssetPath);
                }
                else{
                    std::cout << "err texture" << std::endl;
                    stbi_image_free(data);
                }

                stbi_set_flip_vertically_on_load(true);

                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

                glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

                return cubemapData;
            }

        // Model load Utils
            void AssimpProcessNode(aiNode* node, const aiScene *scene, const String& path, Model& model, std::vector<Texture>& loadedTextures) {
#ifdef SB_BUILD_DEBUG_ASSIMP
                Log::Print("Assim Importer: Processing node, Number of textures: ", loadedTextures.size());
#endif
                for(u32 i = 0; i < node->mNumMeshes; i++){
                    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
                    model.GetMeshes().push_back(AssimpProcessMesh(mesh, scene, path, loadedTextures));
                }
            
                for(u32 i = 0; i < node->mNumChildren; i++){
                    AssimpProcessNode(node->mChildren[i], scene, path, model, loadedTextures);
                }
            }
        
            Mesh AssimpProcessMesh(aiMesh* mesh, const aiScene* scene, const String& path, std::vector<Texture>& loadedTextures){
                std::vector<Vertex> vertices;
                std::vector<unsigned int> indices;
                Material material;
                u16 counter;
                for(u32 i = 0; i < mesh->mNumVertices; i++){
                    Vertex vertex = Vertex();    
                    vertex.position.x = mesh->mVertices[i].x;
                    vertex.position.y = mesh->mVertices[i].y;
                    vertex.position.z = mesh->mVertices[i].z;
                    if(mesh->mNormals[i].Length() > 0) {
                        vertex.normal.x = mesh->mNormals[i].x;
                        vertex.normal.y = mesh->mNormals[i].y;
                        vertex.normal.z = mesh->mNormals[i].z;
                    } 
                    if(mesh->mTextureCoords[0] != nullptr) {
                        vertex.texCoords.x = mesh->mTextureCoords[0][i].x;
                        vertex.texCoords.y = mesh->mTextureCoords[0][i].y;
                    }

                    vertices.push_back(vertex);
                }
                for(u32 i = 0; i < mesh->mNumFaces; i++){
                    aiFace face = mesh->mFaces[i];
                    for(u32 j = 0; j < face.mNumIndices; j++){
                        indices.push_back(face.mIndices[j]);
                    }
                }
                aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
                std::vector<Texture> diffuseTextures = AssimpLoadMaterialTextures(mat, aiTextureType_DIFFUSE, path, loadedTextures);
                std::vector<Texture> specularTextures = AssimpLoadMaterialTextures(mat, aiTextureType_SPECULAR, path, loadedTextures);
                if(diffuseTextures.size() > 0)
                    material._diffuseMap = diffuseTextures.at(0);

                    // TODO - Insert
                // std::vector<Texture> diffuseMaps = AssimpLoadMaterialTextures(mat, aiTextureType_DIFFUSE);
                // material._diffuseMap.insert(material._diffuseMap.end(), diffuseMaps.begin(), diffuseMaps.end());
                // std::vector<Texture> specularMaps = AssimpLoadMaterialTextures(mat, aiTextureType_SPECULAR);

                if(specularTextures.size() > 0)
                    material._specularMap = specularTextures.at(0);

                // textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
                
                return Mesh(vertices, indices, material);
            }
        
            std::vector<Texture> AssimpLoadMaterialTextures(aiMaterial* mat, aiTextureType type, const String& path, std::vector<Texture>& loadedTextures){
                std::vector<Texture> textures;
                for(u32 i = 0; i < mat->GetTextureCount(type); i++){
                    aiString str;
                    mat->GetTexture(type, i, &str);
            
                    //TODO Here a request must be made to texture manager for a new txture or already existing one
                    
                    bool skip = false;
                    for(Texture tex : loadedTextures){

                        // TODO Check if comparison by texture ID works
                        if(std::strcmp(tex.name, str.C_Str()) == 0){
                            textures.push_back(tex);
                            skip = true;
                            break;
                        }
                    }
            
                    if(!skip){
                        String texPath = path + "\\" + String(str.C_Str());
                        Texture texture = LoadTextureResource(texPath, TextureType(type), GL_REPEAT, true, 0);
                        textures.push_back(texture);
                        loadedTextures.push_back(texture);
                    }
                }
                return textures;
            }

        ResourceManager::ResourceManager() : _faceCount(0), _loadedMetadataChunkIndex(0) {
            if(!WriteResourceManifest()) {
                // TODO throw engine subsystem error here
            }
            if(!LoadCommonMetadata()) {
                // TODO throw engine subsystem error here
            }
            if(!LoadResourceMetadata()) {
                // TODO throw engine subsystem error here
            }
        }

        const String ResourceManager::GetAssetPathByAssetID(u32 assetID) {
            if(_pathHashToGUID.contains(assetID)) {
                if(_guidToAssetPathIndex.contains(_pathHashToGUID[assetID])) {
                    return _assetPaths.at(_guidToAssetPathIndex[_pathHashToGUID[assetID]]);
                }
            }
            return "";
        }

        /* TODO
        
           - Each Resource load function needs an edge case error asset so nullptrs or garbage assets are never used/emplaced
        
        */

        SbGUID ResourceManager::GetGUIDByAssetPath(const String& assetPath) {
            // "common/" should indicate that asset belongs to Sandbox Engine domain
            if(assetPath.rfind("common/", 0) == 0 || assetPath.rfind("/common/", 0) == 0) {
                return Crypto::GetGUIDFromHashedInput(assetPath, GUIDDomain::Engine);
            }
            else {
                // Hashing asset path to u32 facilitates actual GUID lookup 
                // pathHashToGUID is filled during startup (res manager metadata)
                u32 hashedAsset = Crypto::GetU32HashFromPath(assetPath);
                return _pathHashToGUID[hashedAsset];
            }
        }

        Model* ResourceManager::LoadModel(const String& assetPath) {
            Model model;
            const SbGUID guid = GetGUIDByAssetPath(assetPath);

            if(!(_modelCache.count(guid) > 0)){
                Model model;
                std::vector<Texture> loadedTextures;

                Assimp::Importer importer;
                const aiScene* scene = importer.ReadFile(assetPath.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
            
                if(!scene || scene->mFlags || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
                    Log::Warn("Assimp Importer: ", importer.GetErrorString());
                    return nullptr;
                }
#ifdef SB_BUILD_DEBUG_ASSIMP
                Log::Info("Assimp Importer: Importing model ", assetPath);
#endif
                String trimmedPath = assetPath.substr(0, std::string(assetPath).find_last_of("/"));
            
#ifdef SB_BUILD_DEBUG_ASSIMP
                Log::Print("Assimp Importer: Scene root node has ", scene->mRootNode->mNumChildren, " children");
#endif
                AssimpProcessNode(scene->mRootNode, scene, trimmedPath, model, loadedTextures);
                model._assetID = Crypto::GetU32HashFromPath(assetPath);
                _modelCache.emplace(guid, ModelCacheData{1, model});
                return &_modelCache[guid].model;
            }
            else{
                _modelCache[guid].refCount++;
                return &_modelCache[guid].model;
            }
            return nullptr;
        }

        Model* ResourceManager::LoadModel(DefaultMesh primitive) {
            
            // Primitive name is placed under Default domain and then hashed
            const SbGUID guid = Crypto::GetGUIDFromHashedInput(primitive.name, GUIDDomain::Default);

            if(!(_modelCache.count(guid) > 0)) {
                Model model;
                model.GetMeshes().push_back(Mesh(primitive.vertices, primitive.indices, Material()));
                model._assetID = Crypto::GetU32HashFromPath(primitive.name);
                _modelCache.emplace(guid, ModelCacheData{1, model});
                return &_modelCache[guid].model;
            }
            else {
                _modelCache[guid].refCount++;

                return &_modelCache[guid].model;
            }
            return nullptr;
        }

        Texture* ResourceManager::LoadTexture(const String& assetPath, TextureType type) {
            const SbGUID guid = GetGUIDByAssetPath(assetPath);
            
            if(!(_textureCache.count(guid) > 0)) {
                Texture texture = LoadTextureResource(assetPath, type, GL_REPEAT, true, 0);
                if(texture.id > 0) {
                    texture.type = type;

                    _textureCache.emplace(guid, TextureCacheData{1, texture});

                    return &_textureCache[guid].texture;
                }
                return nullptr;
            }
            else {
                _textureCache[guid].refCount++;

                return &_textureCache[guid].texture;
            }

            return nullptr;
        }

        Shader* ResourceManager::LoadShader(const String& vertexShaderAssetPath, const String& fragmentShaderAssetPath) {
            ShaderManifestID sID {GetGUIDByAssetPath(vertexShaderAssetPath), GetGUIDByAssetPath(vertexShaderAssetPath)};
            
            if(_shaderCache.count(sID) > 0) {
                _shaderCache[sID].refCount++;

                return &_shaderCache[sID].shader;
            }
            else {
                Shader shader(vertexShaderAssetPath, fragmentShaderAssetPath);

                _shaderCache.emplace(sID, ShaderCacheData{1, shader});

                return &_shaderCache[sID].shader;
            }
            return nullptr;
        }

        Cubemap* ResourceManager::LoadCubemap(const String& rightTextureAssetPath, const String& leftTextureAssetPath, const String& topTextureAssetPath, const String& bottomTextureAssetPath, const String& frontTextureAssetPath, const String& backTextureAssetPath) {
            CubemapManifestID cman {GetGUIDByAssetPath(rightTextureAssetPath), GetGUIDByAssetPath(leftTextureAssetPath), GetGUIDByAssetPath(topTextureAssetPath), GetGUIDByAssetPath(bottomTextureAssetPath), GetGUIDByAssetPath(frontTextureAssetPath), GetGUIDByAssetPath(backTextureAssetPath)};
            
            // Cubemap face texture IDs are used as keys to determine if a certain cubemap was created and exists in cache
            if(!(_cubemapCache.count(cman) > 0)) {
                Cubemap cubemap;

                GLBufferPrimitiveData(cubemap.vertexData, SB_CUBE, 36, 3);
                
                cubemap.data = LoadCubemapTexture(rightTextureAssetPath, leftTextureAssetPath, topTextureAssetPath, bottomTextureAssetPath, frontTextureAssetPath, backTextureAssetPath);

                cubemap._textureFaceRightManifestID = Crypto::GetU32HashFromPath(rightTextureAssetPath);
                cubemap._textureFaceLeftManifestID = Crypto::GetU32HashFromPath(leftTextureAssetPath);
                cubemap._textureFaceTopManifestID = Crypto::GetU32HashFromPath(topTextureAssetPath);
                cubemap._textureFaceBottomManifestID = Crypto::GetU32HashFromPath(bottomTextureAssetPath);
                cubemap._textureFaceFrontManifestID = Crypto::GetU32HashFromPath(frontTextureAssetPath);
                cubemap._textureFaceBackManifestID = Crypto::GetU32HashFromPath(backTextureAssetPath);

                cubemap._cubemapShader = ResourceManagement::LoadShader("common/shaders/cubemap.vert", "common/shaders/cubemap.frag");
                cubemap._cubemapShader->SetInt("skybox", 0);

                _cubemapCache.emplace(cman, CubemapCacheData{1, cubemap});
                return &_cubemapCache[cman].cubemap;
            }
            else {
                _cubemapCache[cman].refCount++;
                
                return &_cubemapCache[cman].cubemap;
            }
            return nullptr;
        }

        void ResourceManager::UnloadModel(SbGUID assetGUID) {
            if(_modelCache.count(assetGUID) > 0) {
                if(_modelCache[assetGUID].refCount > 0) {
                    _modelCache[assetGUID].refCount--;
                }
                if(_modelCache[assetGUID].refCount == 0) {
                    _modelCache.erase(assetGUID);
                }
            }
        }

        void ResourceManager::UnloadTexture(SbGUID assetGUID) {
            if(_textureCache.count(assetGUID) > 0) {
                if(_textureCache[assetGUID].refCount > 0) {
                    _textureCache[assetGUID].refCount--;
                }
                if(_textureCache[assetGUID].refCount == 0) {
                    _textureCache.erase(assetGUID);
                }
            }
        }

        void ResourceManager::UnloadShader(ShaderManifestID assetGUID) {
            if(_shaderCache.count(assetGUID) > 0) {
                if(_shaderCache[assetGUID].refCount > 0) {
                    _shaderCache[assetGUID].refCount--;
                }
                if(_shaderCache[assetGUID].refCount == 0) {
                    _shaderCache.erase(assetGUID);
                }
            }
        }
        
        void ResourceManager::UnloadCubemap(CubemapManifestID assetGUID) {
            if(_cubemapCache.count(assetGUID) > 0) {
                if(_cubemapCache[assetGUID].refCount > 0) {
                    _cubemapCache[assetGUID].refCount--;
                }
                if(_cubemapCache[assetGUID].refCount == 0) {
                    _cubemapCache.erase(assetGUID);
                }
            }
        }

        String ResourceManager::GetYamlResourceNameFromResourceID(ResourceID rId) {
            switch(rId) {
                case ResourceID::SHADER_FRAGMENT:
                    return "fragment";
                break;
                case ResourceID::SHADER_VERTEX:
                    return "vertex";
                break;
                
                case ResourceID::TEXTURE_JPG:
                    return "jpg";
                break;
                case ResourceID::TEXTURE_PNG:
                    return "png";
                break;
                Log::Warn("Resource Manager: Failed to find resource of matching ID.");
                return "";
            }
        }
    
        Resource ResourceManager::GetDataFromID(ResourceID rId, int id) {
            String rName = GetYamlResourceNameFromResourceID(rId);
            Resource rData {0, "", ""};
            YAML::Node resourceNode = YamlUtil::GetNode(SB_RESOURCE_MANIFEST_PATH.c_str(), rName.c_str());
            
            // Wrap this in YAML util function
            int entryId {0};
            auto entries = resourceNode;
            if(entries){
                for(auto entry : entries){
                    entryId = entry["id"].as<int>();
                    if(entryId == id){
                        rData.id = entryId;
                        rData.name = entry["name"].as<std::string>();
                        rData.path = entry["path"].as<std::string>();
                    }
                }
            }
        
            return rData;
        }

        void ResourceManager::LoadPrimitiveMetadata() {
            _pathHashToGUID.emplace(Crypto::GetU32HashFromPath("Cube"), Crypto::GetGUIDFromHashedInput("Cube", GUIDDomain::Default));
            _pathHashToGUID.emplace(Crypto::GetU32HashFromPath("Plane"), Crypto::GetGUIDFromHashedInput("Plane", GUIDDomain::Default));
            _pathHashToGUID.emplace(Crypto::GetU32HashFromPath("Sphere"), Crypto::GetGUIDFromHashedInput("Sphere", GUIDDomain::Default));
            _pathHashToGUID.emplace(Crypto::GetU32HashFromPath("Quad"), Crypto::GetGUIDFromHashedInput("Quad", GUIDDomain::Default));
#ifdef SB_BUILD_DEBUG_RESOURCE_MANAGEMENT
            Log::Print("Cube u32hash: ", Crypto::GetU32HashFromPath("Cube"), " guid: ", Crypto::GetStringFromGUID(Crypto::GetGUIDFromHashedInput("Cube", GUIDDomain::Default)));
            Log::Print("Plane u32hash: ", Crypto::GetU32HashFromPath("Plane"), " guid: ", Crypto::GetStringFromGUID(Crypto::GetGUIDFromHashedInput("Plane", GUIDDomain::Default)));
            Log::Print("Sphere u32hash: ", Crypto::GetU32HashFromPath("Sphere"), " guid: ", Crypto::GetStringFromGUID(Crypto::GetGUIDFromHashedInput("Sphere", GUIDDomain::Default)));
            Log::Print("Quad u32hash: ", Crypto::GetU32HashFromPath("Quad"), " guid: ", Crypto::GetStringFromGUID(Crypto::GetGUIDFromHashedInput("Quad", GUIDDomain::Default)));
#endif
        }

        bool ResourceManager::LoadCommonMetadata() {

            if(!std::filesystem::exists(SB_RESOURCE_COMMON_FOLDER_PATH)) {
                Log::Error("ResourceManager: Failed to load engine assets");
                return false;
            }
            _assetPaths.clear();
            String buffer = "";
            u32 insertedIndex = _assetPaths.size();
            u32 originalSize = insertedIndex;

            LoadPrimitiveMetadata();

            // Register common engine assets into access cache
            for(auto dirEntry : std::filesystem::recursive_directory_iterator(SB_RESOURCE_COMMON_FOLDER_PATH)) {
                buffer = File::ToUnixPathStyle(dirEntry.path().string());
                const SbGUID hashedGuid = Crypto::GetGUIDFromHashedInput(buffer, GUIDDomain::Engine);

                _pathHashToGUID.emplace(Crypto::GetU32HashFromPath(buffer), hashedGuid);
                _guidToAssetPathIndex.emplace(hashedGuid, insertedIndex);
                _assetPaths.push_back(buffer);
                insertedIndex++;

#ifdef SB_BUILD_DEBUG_RESOURCE_MANAGEMENT
                Log::Print("COMMON RES/: Hashed in domain 2 ", buffer, " to U32 hash ", Crypto::GetU32HashFromPath(buffer), " - ", Crypto::GetStringFromGUID(hashedGuid), " index ", insertedIndex);
#endif
            }

            Log::Info("ResourceManager: Cached access metadata for ", insertedIndex-originalSize, " engine assets");
            return true;
        }

        bool ResourceManager::LoadResourceMetadata() {

            YAML::Node manifestAssetsNode;

            if(std::filesystem::exists(SB_RESOURCE_MANIFEST_PATH)) {
                manifestAssetsNode = YAML::LoadFile(SB_RESOURCE_MANIFEST_PATH)["assets"];
            }
            else {
                Log::Error("ResourceManager: Failed to find manifest file");
                return false;
            }
            
            _assetPaths.clear();
            _assetPaths.reserve(manifestAssetsNode.size());
            
            u32 insertedIndex = _assetPaths.size();
            u32 originalSize = insertedIndex;

            for(int i = 0; i < manifestAssetsNode.size(); i++) {
                YAML::Node entry = manifestAssetsNode[i];
                if(!(entry["id"] && entry["path"])) {
                    continue;
                }

                // Asset path is hashed to a u32 key for GUID lookup
                _pathHashToGUID.emplace(Crypto::GetU32HashFromPath(entry["path"].as<std::string>()), Crypto::GetGUIDFromString(entry["id"].as<std::string>()));
                
                // GUID lookup implies using a GUID as lookup key so asset paths are kept with an order ID
                _guidToAssetPathIndex.emplace(Crypto::GetGUIDFromString(entry["id"].as<std::string>()), insertedIndex);
                _assetPaths.push_back(entry["path"].as<std::string>());
                insertedIndex++;
#ifdef SB_BUILD_DEBUG_RESOURCE_MANAGEMENT
                Log::Print("GAME RES/: Hashed ", entry["path"].as<std::string>(), " to ", entry["id"].as<std::string>(), " asset path index ", insertedIndex-1);
#endif
            }
            Log::Info("ResourceManager: Cached access metadata for ", insertedIndex-originalSize, " game assets");
            
            return true;
        }
    }
}