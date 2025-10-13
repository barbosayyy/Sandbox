#include "Core/Base.h"
#include "Core/Config.h"
#include "Core/Types.h"
#include "Core/Utils.h"
#include "ResourceManager.h"
#include "Core/Debug.h"

#include "ResourceManifest.h"
#include "Resources/ResourceManager.h"
#include "Rendering/Primitive.h"
#include "Rendering/OpenGL/GLBuffer.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include "yaml-cpp/yaml.h"

namespace Sb {
    namespace ResourceManagement {

        // Textures
        Texture LoadTextureResource(String& path, TextureType type, GLint wrapMethod, bool flipVertical, bool gammaCorrection);
        u32 LoadCubemapData(u32 rightTextureID, u32 leftTextureID, u32 topTextureID, u32 botTextureID, u32 frontTextureID, u32 backTextureID);
        
        // Assimp (OBJ)
        void AssimpProcessNode(aiNode* node, const aiScene *scene, String& path, Model& model, std::vector<Texture>& loadedTextures);
        std::vector<Texture> AssimpLoadMaterialTextures(aiMaterial* mat, aiTextureType type, String& path, std::vector<Texture>& loadedTextures);
        Mesh AssimpProcessMesh(aiMesh* mesh, const aiScene* scene, String& path, std::vector<Texture>& loadedTextures);

        // Texture load Utils
            Texture LoadTextureResource(String& path, TextureType type, GLint wrapMethod, bool flipVertical, bool gammaCorrection) {
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

            u32 LoadCubemapData(u32 rightTextureID, u32 leftTextureID, u32 topTextureID, u32 botTextureID, u32 frontTextureID, u32 backTextureID) {
                u32 cubemapData;
                
                glGenTextures(1, &cubemapData);
                glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapData);
                stbi_set_flip_vertically_on_load(false);
                
                ResourceManager& res = ResourceManager::GetInstance();
                unsigned char* data;
                int width, height, nChannels;
                data = stbi_load(res.GetAssetMetadata().at(rightTextureID).path, &width, &height, &nChannels, 0);
                if(data){
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+0, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    stbi_image_free(data);
                    Log::Info("ResourceManager: Loaded cubemap face: ", res.GetAssetMetadata().at(rightTextureID).path);
                }
                else{
                    std::cout << "err texture" << std::endl;
                    stbi_image_free(data);
                }
                data = stbi_load(res.GetAssetMetadata().at(leftTextureID).path, &width, &height, &nChannels, 0);
                if(data){
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+1, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    stbi_image_free(data);
                    Log::Info("ResourceManager: Loaded cubemap face: ", res.GetAssetMetadata().at(leftTextureID).path);
                }
                else{
                    std::cout << "err texture" << std::endl;
                    stbi_image_free(data);
                }
                data = stbi_load(res.GetAssetMetadata().at(topTextureID).path, &width, &height, &nChannels, 0);
                if(data){
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+2, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    stbi_image_free(data);
                    Log::Info("ResourceManager: Loaded cubemap face: ", res.GetAssetMetadata().at(topTextureID).path);
                }
                else{
                    std::cout << "err texture" << std::endl;
                    stbi_image_free(data);
                }
                data = stbi_load(res.GetAssetMetadata().at(botTextureID).path, &width, &height, &nChannels, 0);
                if(data){
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+3, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    stbi_image_free(data);
                    Log::Info("ResourceManager: Loaded cubemap face: ", res.GetAssetMetadata().at(botTextureID).path);
                }
                else{
                    std::cout << "err texture" << std::endl;
                    stbi_image_free(data);
                }
                data = stbi_load(res.GetAssetMetadata().at(frontTextureID).path, &width, &height, &nChannels, 0);
                if(data){
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+4, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    stbi_image_free(data);
                    Log::Info("ResourceManager: Loaded cubemap face: ", res.GetAssetMetadata().at(frontTextureID).path);
                }
                else{
                    std::cout << "err texture" << std::endl;
                    stbi_image_free(data);
                }
                data = stbi_load(res.GetAssetMetadata().at(backTextureID).path, &width, &height, &nChannels, 0);
                if(data){
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+5, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    stbi_image_free(data);
                    Log::Info("ResourceManager: Loaded cubemap face: ", res.GetAssetMetadata().at(backTextureID).path);
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
            void AssimpProcessNode(aiNode* node, const aiScene *scene, String& path, Model& model, std::vector<Texture>& loadedTextures) {
                Log::Print("Assim Importer: Processing node, Number of textures: ", loadedTextures.size());
                for(u32 i = 0; i < node->mNumMeshes; i++){
                    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
                    model.GetMeshes().push_back(AssimpProcessMesh(mesh, scene, path, loadedTextures));
                }
            
                for(u32 i = 0; i < node->mNumChildren; i++){
                    AssimpProcessNode(node->mChildren[i], scene, path, model, loadedTextures);
                }
            }
        
            Mesh AssimpProcessMesh(aiMesh* mesh, const aiScene* scene, String& path, std::vector<Texture>& loadedTextures){
                std::vector<Vertex> vertices;
                std::vector<unsigned int> indices;
                Material material;
                u16 counter;
                for(u32 i = 0; i < mesh->mNumVertices; i++){
                    Vertex vertex = Vertex();    
                    vertex.position.x = mesh->mVertices[i].x;
                    vertex.position.y = mesh->mVertices[i].y;
                    vertex.position.z = mesh->mVertices[i].z; 
                    vertex.normal.x = mesh->mNormals[i].x;
                    vertex.normal.y = mesh->mNormals[i].y;
                    vertex.normal.z = mesh->mNormals[i].z;
                    vertex.texCoords.x = mesh->mTextureCoords[0][i].x;
                    vertex.texCoords.y = mesh->mTextureCoords[0][i].y;
            
                    vertices.push_back(vertex);
                }
                for(u32 i = 0; i < mesh->mNumFaces; i++){
                    aiFace face = mesh->mFaces[i];
                    for(u32 j = 0; j < face.mNumIndices; j++){
                        indices.push_back(face.mIndices[j]);
                    }
                }
                aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
                material._diffuseMap = AssimpLoadMaterialTextures(mat, aiTextureType_DIFFUSE, path, loadedTextures).at(0);
                // std::vector<Texture> diffuseMaps = AssimpLoadMaterialTextures(mat, aiTextureType_DIFFUSE);
                // material._diffuseMap.insert(material._diffuseMap.end(), diffuseMaps.begin(), diffuseMaps.end());
                // std::vector<Texture> specularMaps = AssimpLoadMaterialTextures(mat, aiTextureType_SPECULAR);
                material._specularMap = AssimpLoadMaterialTextures(mat, aiTextureType_SPECULAR, path, loadedTextures).at(0);
                // textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
                return Mesh(vertices, indices, material);
            }
        
            std::vector<Texture> AssimpLoadMaterialTextures(aiMaterial* mat, aiTextureType type, String& path, std::vector<Texture>& loadedTextures){
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
            _assetMetadataCache.reserve(SB_RESOURCE_MANAGER_ASSET_ENTRY_LOAD_SIZE);
            
            WriteResourceManifest();
            // Force first metadata chunk load
            LoadMetadata(SB_RESOURCE_MANAGER_ASSET_ENTRY_LOAD_SIZE);
        }

        // TODO: Any reason for Manifest ID and Runtime reference ID to be different?
        Model* ResourceManager::LoadModel(u32 manifestID) {

            // This must be done for default meshes, these could have predetermined indexes in the manifest
            //      _meshes.push_back(Mesh(defaultMesh.vertices, defaultMesh.indices, Material()))

            // Find model in cache and return reference
            if(_modelCache.count(manifestID) > 0) {
                _modelCache[manifestID].refCount++;

                return &_modelCache[manifestID].model;
            }
            // Load model from manifest path
            else {
                if(manifestID < SB_RESOURCE_MANIFEST_MAX_ASSET_ID) {
                    LoadMetadata(manifestID);
                    Model model;
                    std::vector<Texture> loadedTextures;

                    if(_assetMetadataCache.count(manifestID) > 0) {

                        Assimp::Importer importer;
                        const String path = _assetMetadataCache[manifestID].path;
                        const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
                    
                        if(!scene || scene->mFlags || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
                            Log::Warn("Assimp Importer: ", importer.GetErrorString());
                            return nullptr;
                        }
                        Log::Info("Assimp Importer: Importing model ", path);
                        String trimmedPath = std::string(path).substr(0, std::string(path).find_last_of("\\"));
                    
                        Log::Print("Assimp Importer: Scene root node has ", scene->mRootNode->mNumChildren, " children");
                        
                        AssimpProcessNode(scene->mRootNode, scene, trimmedPath, model, loadedTextures);

                        model._assetID = manifestID;

                        _modelCache.emplace(manifestID, ModelCacheData{1, model});
                        
                        return &_modelCache[manifestID].model;
                    }
                }
                else {
                    Model model;
                    DefaultMesh mesh = GetPrimitiveMeshByID(manifestID);
                    model.GetMeshes().push_back(Mesh(mesh.vertices, mesh.indices, Material()));
                    _modelCache.emplace(manifestID, ModelCacheData{1, model});
                    return &_modelCache[manifestID].model;
                }
                return nullptr;
            }
        }

        Texture* ResourceManager::LoadTexture(u32 manifestID, TextureType type) {
            if(_textureCache.count(manifestID) > 0) {
                _textureCache[manifestID].refCount++;

                return &_textureCache[manifestID].texture;
            }

            // Load texture from manifest path
            else {
                LoadMetadata(manifestID);
                if(_assetMetadataCache.count(manifestID) > 0) {

                    // TODO provide wrap method
                    String path = _assetMetadataCache[manifestID].path;
                    Texture texture = LoadTextureResource(path, type, GL_REPEAT, true, 0);

                    if(texture.id > 0) {
                        texture.assetID = manifestID;
                        texture.type = type;

                        _textureCache.emplace(manifestID, TextureCacheData{1, texture});

                        return &_textureCache[manifestID].texture;
                    }
                }
                return nullptr;
            }
        }

        Shader* ResourceManager::LoadShader(u32 vertexManifestID, u32 fragmentManifestID) {
            ShaderManifestID sID {vertexManifestID, fragmentManifestID};
            
            if(_shaderCache.count(sID) > 0) {
                _shaderCache[sID].refCount++;

                return &_shaderCache[sID].shader;
            }
            else {
                LoadMetadata(vertexManifestID);
                LoadMetadata(fragmentManifestID);
                if(_assetMetadataCache.count(vertexManifestID) > 0 && _assetMetadataCache.count(fragmentManifestID) > 0) {
                    Shader shader(_assetMetadataCache[vertexManifestID].path.c_str(), _assetMetadataCache[fragmentManifestID].path.c_str());
                    shader._assetID.vertexManifestID = sID.vertexManifestID;
                    shader._assetID.fragmentManifestID = sID.fragmentManifestID;

                    _shaderCache.emplace(sID, ShaderCacheData{1, shader});

                    return &_shaderCache[sID].shader;
                }
            }
            return nullptr;
        }

        Cubemap* ResourceManager::LoadCubemap(u32 rightTextureID, u32 leftTextureID, u32 topTextureID, u32 botTextureID, u32 frontTextureID, u32 backTextureID) {
            CubemapManifestID cman {rightTextureID, leftTextureID, topTextureID, botTextureID, frontTextureID, backTextureID};
            
            // Cubemap face texture IDs are used as keys to determine if a certain cubemap was created and exists in cache
            if(_cubemapCache.count(cman) > 0) {
                _cubemapCache[cman].refCount++;
                
                return &_cubemapCache[cman].cubemap;
            }
            else {
                Cubemap cubemap;

                GLBufferPrimitiveData(cubemap.vertexData, SB_CUBE, 36, 3);
                
                cubemap.data = LoadCubemapData(rightTextureID, leftTextureID, topTextureID, botTextureID, frontTextureID, backTextureID);
                
                cubemap._cubemapShader = ResourceManager::LoadShader(34, 33);
                cubemap._cubemapShader->SetInt("skybox", 0);

                _cubemapCache.emplace(cman, CubemapCacheData{1, cubemap});
                return &_cubemapCache[cman].cubemap;
            }
            return nullptr;
        }

        void ResourceManager::UnloadModel(u32 manifestID) {
            if(_modelCache.count(manifestID) > 0) {
                if(_modelCache[manifestID].refCount > 0) {
                    _modelCache[manifestID].refCount--;
                }
                if(_modelCache[manifestID].refCount == 0) {
                    _modelCache.erase(manifestID);
                }
            }
        }

        void ResourceManager::UnloadTexture(u32 manifestID) {
            if(_textureCache.count(manifestID) > 0) {
                if(_textureCache[manifestID].refCount > 0) {
                    _textureCache[manifestID].refCount--;
                }
                if(_textureCache[manifestID].refCount == 0) {
                    _textureCache.erase(manifestID);
                }
            }
        }

        void ResourceManager::UnloadShader(ShaderManifestID shaderManifestID) {
            if(_shaderCache.count(shaderManifestID) > 0) {
                if(_shaderCache[shaderManifestID].refCount > 0) {
                    _shaderCache[shaderManifestID].refCount--;
                }
                if(_shaderCache[shaderManifestID].refCount == 0) {
                    _shaderCache.erase(shaderManifestID);
                }
            }
        }

        void ResourceManager::UnloadShader(u32 vertexManifestID, u32 fragmentManifestID) {
            ShaderManifestID sID{vertexManifestID, fragmentManifestID};
            if(_shaderCache.count(sID) > 0) {
                if(_shaderCache[sID].refCount > 0) {
                    _shaderCache[sID].refCount--;
                }
                if(_shaderCache[sID].refCount == 0) {
                    _shaderCache.erase(sID);
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

        bool ResourceManager::LoadMetadata(u32 targetLoadPtr) {

            // No loaded metadata for asset - Load whole metadata
            if(!(_assetMetadataCache.count(targetLoadPtr) > 0)) {
                
                u32 targetCurrentLoadNum;

                YAML::Node manifestAssetsNode = YAML::LoadFile(SB_RESOURCE_MANIFEST_PATH)["assets"];

                manifestSize = manifestAssetsNode.size();

                // Determine target lookahead
                if(manifestSize > _loadedMetadataChunkIndex+SB_RESOURCE_MANAGER_ASSET_ENTRY_LOAD_SIZE) {
                    targetCurrentLoadNum = _loadedMetadataChunkIndex+SB_RESOURCE_MANAGER_ASSET_ENTRY_LOAD_SIZE;
                }
                else {
                    targetCurrentLoadNum = manifestSize;
                }

                Log::Info("ResourceManager: Missing asset metadata, loading metadata for ", targetCurrentLoadNum, " assets");

                for(size_t i = _loadedMetadataChunkIndex; i < targetCurrentLoadNum; i++) {
                    YAML::Node entry = manifestAssetsNode[i];
                    _assetMetadataCache.emplace(entry["id"].as<u32>(), 
                    AssetMetadata{entry["name"].as<std::string>(), entry["path"].as<std::string>()});
                }

                // TODO Implement load size limit
                _loadedMetadataChunkIndex = targetCurrentLoadNum;
                if(!(_assetMetadataCache.count(targetLoadPtr) > 0) && manifestSize > _loadedMetadataChunkIndex) {
                    return LoadMetadata(targetLoadPtr);
                }
                else if(!(_assetMetadataCache.count(targetLoadPtr) > 0)) {
                    return false;
                }
                else{
                    Log::Info("ResourceManager: Finished loading metadata - Loaded ", (sizeof(_assetMetadataCache.begin()->first)+sizeof(_assetMetadataCache.begin()->second))*_assetMetadataCache.size(), " bytes");
                    return true;
                }
            }
            return true;
        }
    }
}