#pragma once

#include "Mesh.h"
#include "Renderer.h"

#include "assimp/scene.h"

namespace Sb {
    class Model{
    public:
        Model(const char* path);
        void Draw(Shader* shader, Renderer* renderer, vec3 pos);
        
        u32 _fCount;
        vec3 _pos;
    protected:
        std::vector<Mesh> _meshes;
        std::vector<Texture> _loadedTextures;

        String _directory;
        
        u32 _vCount;
        
        void LoadModel(String path);
        void ProcessNode(aiNode* node, const aiScene *scene);
        std::vector<Texture> AssimpLoadMaterialTextures(aiMaterial* mat, aiTextureType type);
        Mesh AssimpProcessMesh(aiMesh* mesh, const aiScene* scene);
        //u32 TextureFromFile(const char* path, bool gamma);
    };
}