#include "Core/Debug.h"
#include "Model.h"

#include "Core/Base.h"

namespace Sb {

    static Mesh emptyMesh = Mesh();
    
    Model::Model() : _vCount(0), _fCount(0) {
    }
    
    void Model::Draw(Renderer* renderer, vec3 pos, vec3 rot, vec3 scale)
    {
        if(_meshes.size() > 0) {
            for(Mesh mesh : _meshes) {
                mesh.Draw(renderer, pos, rot, scale);
            }
        }
    }

    Mesh& Model::GetMesh(u32 index) {
            
        if(index < _meshes.size()) {
            return _meshes[index];
        }
        Log::Warn("Model: Failed to find mesh, returning empty mesh");
        return emptyMesh;
    }
}
