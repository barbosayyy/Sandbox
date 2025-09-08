#include "Primitive.h"
#include "Core/Base.h"
#include "Core/Types.h"

#include <iterator>

namespace Sb {
    DefaultMesh Primitive::GetCube() {
        if(cube.vertices.empty() == true) {
            constexpr size_t floatsPerVertex = 3;
            const size_t vCount = sizeof(SB_CUBE_VERTICES) / sizeof(u32) * floatsPerVertex;
            const size_t iCount = sizeof(SB_CUBE_INDICES) / sizeof(u32);

            cube.vertices.reserve(vCount);
            cube.indices.reserve(iCount);

            vec3 pos;
            const vec3 norm(0.0f); // temp
            const vec3 tex(0.0f); // temp
            for(int i = 0; i < vCount * floatsPerVertex; i += floatsPerVertex) {
                pos.x = SB_CUBE_VERTICES[i];
                pos.y = SB_CUBE_VERTICES[i+1];
                pos.z = SB_CUBE_VERTICES[i+2];
                cube.vertices.emplace_back(Vertex(pos, norm, tex));
            }
        }
        return cube;
    }

    DefaultMesh Primitive::GetPlane() {return Primitive::plane;}
    DefaultMesh Primitive::GetSphere() {return Primitive::sphere;}
    DefaultMesh Primitive::GetQuad() {return Primitive::quad;}
}
