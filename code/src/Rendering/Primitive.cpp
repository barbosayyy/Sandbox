#include "Primitive.h"
#include "Core/Base.h"
#include "Core/Types.h"

#include <iterator>

namespace Sb {
    DefaultMesh Primitive::cube {};
    DefaultMesh Primitive::plane {};
    DefaultMesh Primitive::sphere {};
    DefaultMesh Primitive::quad {};


    DefaultMesh Primitive::GetCube() {
        if(Primitive::cube.vertices.empty() == true) {
            constexpr size_t floatsPerVertex = 8;
            const size_t vCount = sizeof(SB_CUBE_VERTICES) / (sizeof(float) * floatsPerVertex);
            const size_t iCount = sizeof(SB_CUBE_INDICES) / sizeof(u32);

            Primitive::cube.vertices.reserve(vCount);
            Primitive::cube.indices.reserve(iCount);

            vec3 pos;
            vec3 norm;
            vec2 tex;
            for(int i = 0; i < vCount * floatsPerVertex; i += floatsPerVertex) {
                pos.x = SB_CUBE_VERTICES[i];
                pos.y = SB_CUBE_VERTICES[i+1];
                pos.z = SB_CUBE_VERTICES[i+2];
                norm.x = SB_CUBE_VERTICES[i+3];
                norm.y = SB_CUBE_VERTICES[i+4];
                norm.z = SB_CUBE_VERTICES[i+5];
                tex.x = SB_CUBE_VERTICES[i+6];
                tex.y = SB_CUBE_VERTICES[i+7];
                Primitive::cube.vertices.emplace_back(Vertex(pos, norm, tex));
            }

            for(int i = 0; i < iCount; i++) {
                Primitive::cube.indices.emplace_back(SB_CUBE_INDICES[i]);
            }
        }
        return Primitive::cube;
    }

    DefaultMesh Primitive::GetSphere(float radius, u32 stacks, u32 sectors) {
        Primitive::sphere.vertices.clear();
        Primitive::sphere.indices.clear();

        float x, y, z, xy;
        float nx, ny, nz, lengthInv = 1.0f / radius;
        float s, t;
        
        float sectorStep = 2 * PI / sectors;
        float stackStep = PI / stacks;
        float sectorAngle, stackAngle;
        
        // Vertices
        for(int i = 0; i <= stacks; ++i) {
            stackAngle = PI / 2 - i * stackStep;
            xy = radius * cosf(stackAngle);
            z = radius * sinf(stackAngle);
            
            for(int j = 0; j <= sectors; ++j) {
                sectorAngle = j * sectorStep;
                
                // Vertex position
                x = xy * cosf(sectorAngle);
                y = xy * sinf(sectorAngle);
                
                // Normalized normal
                nx = x * lengthInv;
                ny = y * lengthInv;
                nz = z * lengthInv;
                
                // Texture coordinates
                s = (float)j / sectors;
                t = (float)i / stacks;

                Primitive::sphere.vertices.push_back(Vertex(vec3(x,y,z), vec3(nx, ny, nz), vec2(s, j)));
            }
        }
        
        // Indices
        u32 k1, k2;
        for(int i = 0; i < stacks; ++i) {
            k1 = i * (sectors + 1);
            k2 = k1 + sectors + 1;
            
            for(int j = 0; j < sectors; ++j, ++k1, ++k2) {
                if(i != 0) {
                    Primitive::sphere.indices.push_back(k1);
                    Primitive::sphere.indices.push_back(k2);
                    Primitive::sphere.indices.push_back(k1 + 1);
                }
                
                if(i != (stacks - 1)) {
                    Primitive::sphere.indices.push_back(k1 + 1);
                    Primitive::sphere.indices.push_back(k2);
                    Primitive::sphere.indices.push_back(k2 + 1);
                }
            }
        }
        
        return Primitive::sphere;
    }

    DefaultMesh Primitive::GetPlane() {return Primitive::plane;}
    DefaultMesh Primitive::GetQuad() {return Primitive::quad;}
}
