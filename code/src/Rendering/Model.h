#pragma once

#include "Core/Types.h"
#include "Mesh.h"
#include "Renderer.h"

#include "assimp/scene.h"

namespace Sb {
    class Model{
    protected:
        std::vector<Mesh> _meshes;
        std::vector<Texture> _loadedTextures;  
        u32 _vCount;
        u32 _fCount;
    
    public:
        u32 _assetID;
        Model();
        
        void Draw(Renderer* renderer, vec3 pos, vec3 rot, vec3 scale);
        Mesh& GetMesh(u32 index);
        std::vector<Mesh>& GetMeshes() {return _meshes;};
        u32 GetFaceCount() const { return _fCount; };
        u32 GetVertexCount() const { return _vCount; };
    };
}