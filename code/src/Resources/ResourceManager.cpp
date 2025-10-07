#include "Core/Config.h"
#include "Core/Types.h"
#include "Core/Utils.h"
#include "ResourceManager.h"
#include "Core/Debug.h"

#include "Resources/ResourceManager.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include "yaml-cpp/yaml.h"

namespace Sb {
    namespace ResourceManagement {

        Texture LoadTextureResource(String& path, TextureType type, GLint wrapMethod, bool flipVertical, bool gammaCorrection);
        void AssimpProcessNode(aiNode* node, const aiScene *scene, String& path, Model& model, std::vector<Texture>& loadedTextures);
        std::vector<Texture> AssimpLoadMaterialTextures(aiMaterial* mat, aiTextureType type, String& path, std::vector<Texture>& loadedTextures);
        Mesh AssimpProcessMesh(aiMesh* mesh, const aiScene* scene, String& path, std::vector<Texture>& loadedTextures);
        
        // Texture load Utils
            Texture LoadTextureResource(String& path, TextureType type, GLint wrapMethod, bool flipVertical, bool gammaCorrection) {
                Texture texture;

                texture.name = std::string(path).substr(std::string(path).find_last_of("/")+1, std::string(path).size());

                glGenTextures(1, &texture.id);

                stbi_set_flip_vertically_on_load(flipVertical);
		        u8* data = stbi_load(path, &texture.width, &texture.height, &texture.numChannels, 0);

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
                        String texPath = path + "/" + String(str.C_Str());
                        Texture texture = LoadTextureResource(texPath, TextureType(type), GL_REPEAT, true, 0);
                        textures.push_back(texture);
                        loadedTextures.push_back(texture);
                    }
                }
                return textures;
            }

        ResourceManager::ResourceManager() : _faceCount(0) {
            _manifestAssetsNode = YAML::LoadFile(SB_RESOURCE_MANIFEST_PATH)["assets"];
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

                Model model;
                std::vector<Texture> loadedTextures;

                if(_manifestAssetsNode[manifestID]) {

                    Assimp::Importer importer;
                    const String path = _manifestAssetsNode[manifestID]["path"].as<std::string>();
                    const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
                
                    if(!scene || scene->mFlags || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
                        Log::Warn("Assimp Importer: ", importer.GetErrorString());
                        return nullptr;
                    }
                    Log::Info("Assimp Importer: Importing model ", path);
                    String trimmedPath = std::string(path).substr(0, std::string(path).find_last_of("/"));
                
                    Log::Print("Assimp Importer: Scene root node has ", scene->mRootNode->mNumChildren, " children");
                    
                    AssimpProcessNode(scene->mRootNode, scene, trimmedPath, model, loadedTextures);

                    model._assetID = manifestID;

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
                if(_manifestAssetsNode[manifestID]) {

                    // TODO provide wrap method
                    String path = _manifestAssetsNode[manifestID]["path"].as<std::string>();
                    Texture texture = LoadTextureResource(path, type, GL_REPEAT, true, 0);

                    if(texture.id > 0) {
                        texture.assetID = manifestID;

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
                Shader shader(_manifestAssetsNode[vertexManifestID]["path"].as<std::string>().c_str(), _manifestAssetsNode[fragmentManifestID]["path"].as<std::string>().c_str());
                shader._assetID.vertexManifestID = sID.vertexManifestID;
                shader._assetID.fragmentManifestID = sID.fragmentManifestID;

                _shaderCache.emplace(sID, ShaderCacheData{1, shader});

                return &_shaderCache[sID].shader;
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
    }
}