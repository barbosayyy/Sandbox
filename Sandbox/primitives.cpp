#include "primitives.h"
#include "vertex_buffer.h"

Triangle::Triangle() {
	Triangle::create();
}

Triangle::~Triangle() {

}

void Triangle::create() {
    float vertices[] = {
         -0.5f,  -0.5f, 0.0f,  // top right
         0.0f, 0.5f, 0.0f,  // bottom right
        0.5f, -0.5f, 0.0f,  // bottom left
    };
    unsigned int vertexCount{ 3 };

    vb = new VertexBuffer(vertices, vertexCount);
}

void Triangle::draw() {
    vb->draw();
}