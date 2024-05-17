#pragma once 

#include <vector>
#include "Mesh.h"

#include "assimp/material.h"
#include "assimp/mesh.h"
#include "assimp/scene.h"

namespace Sandbox{
    std::vector<Texture> LoadAssimpMaterialTextures(aiMaterial* mat, aiTextureType type);
    Mesh ProcessAssimpMesh(aiMesh* mesh, const aiScene* scene);
}