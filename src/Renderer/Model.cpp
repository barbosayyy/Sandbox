#include "../Core/Debug.h"
#include "Assimp.h"
#include "Model.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

using namespace Sandbox;

Model::Model(const char* path)
{
    LoadModel(path);
}

void Model::Draw(Shader* shader)
{
    if(_meshes.size() > 0){
        for(Mesh mesh : _meshes){
            mesh.Draw(shader);
        }
    }
}

void Model::LoadModel(String path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        Logger::Trace(LogLevel::ERROR, "Assimp Importer: ", importer.GetErrorString());
        return;
    }
    Logger::Trace(LogLevel::RUNTIME, "Assimp Importer: ", "importing model");
    directory = std::string(path).substr(0, std::string(path).find_last_of("/"));
    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene *scene)
{
    for(u32 i = 0; i < node->mNumMeshes; i++){
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        Debugger::Print("Processing Mesh");
        _meshes.push_back(ProcessAssimpMesh(mesh, scene));
    }
    for(u32 i = 0; i < node->mNumChildren; i++){
        Debugger::Print("Processing Node");
        ProcessNode(node->mChildren[i], scene);
    }
}