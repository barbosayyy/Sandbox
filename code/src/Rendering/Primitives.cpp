#include "Primitives.h"

using namespace SbEngine;

Square::Square(float x, float y, float z) : Renderable(x, y, z)
{
    Square::Create();
}

Square::Square() : Renderable()
{
    Square::Create();
}

Square::~Square()
{
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

Cube::Cube(float x, float y, float z) : Renderable(x, y, z)
{
    Cube::Create();
}

Cube::Cube() : Renderable()
{
    Cube::Create();
}

Cube::~Cube()
{
}

void Cube::Create()
{
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

void Cube::Draw(Renderer* renderer)
{
    Renderable::Draw(renderer);
}

Plane::Plane(float x, float y, float z) : Renderable(x, y, z)
{
    Plane::Create();
}

Plane::~Plane(){

}

Plane::Plane() : Renderable()
{
    Plane::Create();
}

void Plane::Create()
{
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