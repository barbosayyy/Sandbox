#include "../Core/Debug.h"
#include "Assimp.h"
#include "Model.h"

#include "Core/Base.h"
#include "NewMaterial.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "stb_image/stb_image.h"

using namespace Sb;

Model::Model() : _vCount(0), _fCount(0) {
    // LoadModel(path);
    // for(Mesh mesh : _meshes){
    //     _vCount += mesh._vertices.size();
    // };
    // Log::Info("Assimp Importer: Loaded model with ", _meshes.size(), " meshes ", _loadedTextures.size(), " textures ", _fCount," faces ", _vCount, " vertices");
}

void Model::Draw(Renderer* renderer, vec3 pos)
{
    if(_meshes.size() > 0) {
        for(Mesh mesh : _meshes) {
            mesh.Draw(renderer, pos);
        }
    }
}

void Model::LoadModel(float* mesh) {
    _meshes.push_back(Mesh(mesh, SB_CUBE_INDICES, NewMaterial()));
}

void Model::LoadModel(String path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
    // std::vector<Texture> totalLoadedTextures;

    if(!scene || scene->mFlags || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        Log::Warn("Assimp Importer: ", importer.GetErrorString());
        return;
    }
    Log::Info("Assimp Importer: Importing model ", path);
    String trimmedPath = std::string(path).substr(0, std::string(path).find_last_of("/"));

    Log::Print("Assimp Importer: Scene root node has ", scene->mRootNode->mNumChildren, " children");

    ProcessNode(scene->mRootNode, scene, trimmedPath);
}

void Model::ProcessNode(aiNode* node, const aiScene *scene, String path) {
    Log::Print("Assim Importer: Processing node, Number of textures: ", _loadedTextures.size());
    for(u32 i = 0; i < node->mNumMeshes; i++){
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        _fCount += mesh->mNumFaces;
        _meshes.push_back(AssimpProcessMesh(mesh, scene, path));
    }

    for(u32 i = 0; i < node->mNumChildren; i++){
        ProcessNode(node->mChildren[i], scene, path);
    }
}

Mesh Model::AssimpProcessMesh(aiMesh* mesh, const aiScene* scene, String path){
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    NewMaterial material;
    u16 counter;
    for(u32 i = 0; i < mesh->mNumVertices; i++){
        Vertex vertex;
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
    material._diffuseMap = AssimpLoadMaterialTextures(mat, aiTextureType_DIFFUSE, path);
    // std::vector<Texture> diffuseMaps = AssimpLoadMaterialTextures(mat, aiTextureType_DIFFUSE);
    // material._diffuseMap.insert(material._diffuseMap.end(), diffuseMaps.begin(), diffuseMaps.end());
    // std::vector<Texture> specularMaps = AssimpLoadMaterialTextures(mat, aiTextureType_SPECULAR);
    material._specularMap = AssimpLoadMaterialTextures(mat, aiTextureType_SPECULAR, path);
    // textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    return Mesh(vertices, indices, material);
}

std::vector<Texture> Model::AssimpLoadMaterialTextures(aiMaterial* mat, aiTextureType type, String path){
    std::vector<Texture> textures;
    for(u32 i = 0; i < mat->GetTextureCount(type); i++){
        aiString str;
        mat->GetTexture(type, i, &str);

        //TEMP: Here a request must be made to texture manager for a new txture or already existing one
        bool skip = false;
        for(Texture tex : _loadedTextures){
            if(std::strcmp(tex._name, str.C_Str()) == 0){
                textures.push_back(tex);
                skip = true;
                break;
            }
        }

        if(!skip){
            String texPath = path + "/" + String(str.C_Str());
            Texture texture(texPath.c_str(), TextureType(type), GL_REPEAT, true, 0);
            textures.push_back(texture);
            _loadedTextures.push_back(texture);
        }
    }
    return textures;
}