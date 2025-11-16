#include "Primitive.h"
#include "Core/Base.h"
#include "Core/Config.h"
#include "Core/Types.h"
#include "DefaultPrimitives.h"

namespace Sb {
    DefaultMesh Primitive::cube {"Cube"};
    DefaultMesh Primitive::plane {"Plane"};
    DefaultMesh Primitive::sphere {"Sphere"};
    DefaultMesh Primitive::quad {"Quad"};

    DefaultMesh GetPrimitiveMeshByID(u32 ID) {
        switch(ID) {
            case(SB_RESOURCE_MANIFEST_MESH_CUBE_ID):
                return Primitive::GetCube();
            case(SB_RESOURCE_MANIFEST_MESH_PLANE_ID):
                return Primitive::GetPlane();
            case(SB_RESOURCE_MANIFEST_MESH_SPHERE_ID):
                return Primitive::GetSphere(1, 32, 32);
            case(SB_RESOURCE_MANIFEST_MESH_QUAD_ID):
                return Primitive::GetQuad();
            break;
        }
        return Primitive::GetCube();
    }

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

    DefaultMesh Primitive::GetPlane() {
        if(Primitive::plane.vertices.empty() == true) {
            constexpr size_t floatsPerVertex = 8;
            const size_t vCount = sizeof(SB_PLANE_VERTICES) / (sizeof(float) * floatsPerVertex);
            const size_t iCount = sizeof(SB_PLANE_INDICES) / sizeof(u32);

            Primitive::plane.vertices.reserve(vCount);
            Primitive::plane.indices.reserve(iCount);

            vec3 pos;
            vec3 norm;
            vec2 tex;
            for(int i = 0; i < vCount * floatsPerVertex; i += floatsPerVertex) {
                pos.x = SB_PLANE_VERTICES[i];
                pos.y = SB_PLANE_VERTICES[i+1];
                pos.z = SB_PLANE_VERTICES[i+2];
                norm.x = SB_PLANE_VERTICES[i+3];
                norm.y = SB_PLANE_VERTICES[i+4];
                norm.z = SB_PLANE_VERTICES[i+5];
                tex.x = SB_PLANE_VERTICES[i+6];
                tex.y = SB_PLANE_VERTICES[i+7];
                Primitive::plane.vertices.emplace_back(Vertex(pos, norm, tex));
            }

            for(int i = 0; i < iCount; i++) {
                Primitive::plane.indices.emplace_back(SB_PLANE_INDICES[i]);
            }
        }
        return Primitive::plane;
    }
    DefaultMesh Primitive::GetQuad() {return Primitive::quad;}
}
