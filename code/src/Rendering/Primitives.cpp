#include "Primitives.h"
#include "Rendering/IndexBuffer.h"
#include <vector>

using namespace Sb;

Square::Square(float x, float y, float z) : Renderable(x, y, z){
    Square::Create();
}

Square::Square() : Renderable(){
    Square::Create();
}

Square::~Square(){
}

void Square::Create(){
    float vertices[] = {
        /*
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
        */
        -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f, 1.0f
    };
    unsigned int indices[]{
        0, 1, 2,
        2, 3, 0
    };

    unsigned int vertexCount{ 4 };
    unsigned int indexCount{ 6 };

    _vb = new VertexBuffer(vertices, vertexCount);
    _eb = new IndexBuffer(indices, indexCount);
}

void Square::Draw(Renderer* renderer) {
    Renderable::Draw(renderer);
}

Cube::Cube(float x, float y, float z) : Renderable(x, y, z){
    Cube::Create();
}

Cube::Cube() : Renderable(){
    Cube::Create();
}

Cube::~Cube(){
}

void Cube::Create(){
    float vertices[] = {
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,

        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,1.0f, 1.0f
    };
    unsigned int indices[] {
        0, 1, 2,
         2, 3, 0,
         4, 5, 6,
         6, 7, 4,
         8, 9, 10,
         10, 11, 8,
         12, 13, 14,
         14, 15, 12,
         16, 17, 18,
         18, 19, 16,
         20, 21, 22,
         22, 23, 20
    };

    unsigned int vertexCount{ 24 };
    unsigned int indicesCount { 36 };
    _vb = new VertexBuffer(vertices, vertexCount);
    _eb = new IndexBuffer(indices, indicesCount);
}

void Cube::Draw(Renderer* renderer){
    Renderable::Draw(renderer);
}

Plane::Plane(float x, float y, float z) : Renderable(x, y, z){
    Plane::Create();
}

Plane::~Plane(){

}

Plane::Plane() : Renderable(){
    Plane::Create();
}

void Plane::Create(){
    float vertices[] = {
        -0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    unsigned int vertexCount{4};
    unsigned int indexCount{6};

    _vb = new VertexBuffer(vertices, vertexCount);
    _eb = new IndexBuffer(indices, indexCount); 
}



void Plane::Draw(Renderer* renderer){
    Renderable::Draw(renderer);
}

Sphere::Sphere(float radius, int sectors, int stacks) : Renderable(), _radius(radius), _sectors(sectors), _stacks(stacks){
    Sphere::Create();
}

Sphere::Sphere(float radius, int sectors, int stacks, vec3 position) : Renderable(position.x, position.y, position.z), _radius(radius), _sectors(sectors), _stacks(stacks){
    Sphere::Create();
}

Sphere::~Sphere(){
    
}

void Sphere::Create(){
    std::vector<float> vertices;
    std::vector<u32> indices;

    vertices.clear();
    indices.clear();

    float x, y, z, xy;
    float nx, ny, nz, lengthInv = 1.0f / _radius;
    float s, t;
    
    float sectorStep = 2 * PI / _sectors;
    float stackStep = PI / _stacks;
    float sectorAngle, stackAngle;
    
    // Vertices
    for(int i = 0; i <= _stacks; ++i) {
        stackAngle = PI / 2 - i * stackStep;
        xy = _radius * cosf(stackAngle);
        z = _radius * sinf(stackAngle);
        
        for(int j = 0; j <= _sectors; ++j) {
            sectorAngle = j * sectorStep;
            
            // Vertex position
            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            
            // Normalized normal
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            
            // Texture coordinates (not used here but included for completeness)
            s = (float)j / _sectors;
            t = (float)i / _stacks;
            
            // Add vertex data
            vertices.push_back(x);  // X
            vertices.push_back(y);  // Y
            vertices.push_back(z);  // Z
            vertices.push_back(nx); // Normal X
            vertices.push_back(ny); // Normal Y
            vertices.push_back(nz); // Normal Z
        }
    }
    
    // Indices
    u32 k1, k2;
    for(int i = 0; i < _stacks; ++i) {
        k1 = i * (_sectors + 1);
        k2 = k1 + _sectors + 1;
        
        for(int j = 0; j < _sectors; ++j, ++k1, ++k2) {
            if(i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            
            if(i != (_stacks - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    this->_vb = new VertexBuffer(vertices);
    this->_eb = new IndexBuffer(indices);
}

void Sphere::Draw(Renderer* renderer){
    Renderable::Draw(renderer);
}