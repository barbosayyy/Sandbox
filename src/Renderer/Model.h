#pragma once

#include "Mesh.h"
#include "Renderer.h"

#include "assimp/scene.h"

namespace Sandbox{
    class Model{
    public:
        Model(const char* path);
        void Draw(Shader* shader, Renderer* renderer);

    protected:
        std::vector<Mesh> _meshes;
        std::vector<Texture> _loadedTextures;

        String _directory;
        
        u32 _vCount;
        u32 _fCount;
        
        void LoadModel(String path);
        void ProcessNode(aiNode* node, const aiScene *scene);
        std::vector<Texture> AssimpLoadMaterialTextures(aiMaterial* mat, aiTextureType type);
        Mesh AssimpProcessMesh(aiMesh* mesh, const aiScene* scene);
        //u32 TextureFromFile(const char* path, bool gamma);
    };
}