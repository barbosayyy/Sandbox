#pragma once

#include "Mesh.h"

#include "assimp/scene.h"

namespace Sandbox{
    class Model{
    public:
        Model(const char* path);
        void Draw(Shader* shader);

    protected:
        std::vector<Mesh> _meshes;
        String directory;
        void LoadModel(String path);
        void ProcessNode(aiNode* node, const aiScene *scene);
    };
}