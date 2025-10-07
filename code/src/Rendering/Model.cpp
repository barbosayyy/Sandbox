#include "../Core/Debug.h"
#include "Model.h"

#include "Core/Base.h"
#include "Material.h"
#include "Resources/ResourceManager.h"

namespace Sb {

    static Mesh emptyMesh = Mesh();
    
    Model::Model() : _vCount(0), _fCount(0) {
    }
    
    void Model::Draw(Renderer* renderer, vec3 pos)
    {
        if(_meshes.size() > 0) {
            for(Mesh mesh : _meshes) {
                mesh.Draw(renderer, pos);
            }
        }
    }
    
    void Model::LoadModel(u32 assetID) {
        ResourceManagement::ResourceManager& resManager = ResourceManagement::ResourceManager::GetInstance();

        resManager.LoadModel(assetID);
    }

    Mesh& Model::GetMesh(u32 index) {
            
        if(index < _meshes.size()) {
            return _meshes[index];
        }
        Log::Warn("Model: Failed to find mesh, returning empty mesh");
        return emptyMesh;
    }
}
