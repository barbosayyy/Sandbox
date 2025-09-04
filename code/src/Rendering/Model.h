#pragma once

#include "Mesh.h"
#include "Renderer.h"

#include "assimp/scene.h"

namespace Sb {
    class Model{
    public:
        Model();
        
        void Draw(Renderer* renderer, vec3 pos);
        void LoadModel(String path);
        void LoadModel(float* mesh);
        
        u32 _fCount;
        vec3 _pos;
    protected:
        void ProcessNode(aiNode* node, const aiScene *scene, String path);
        std::vector<Texture> AssimpLoadMaterialTextures(aiMaterial* mat, aiTextureType type, String path);
        Mesh AssimpProcessMesh(aiMesh* mesh, const aiScene* scene, String path);

        std::vector<Mesh> _meshes;
        u32 _vCount;
        std::vector<Texture> _loadedTextures;
        
    };
}