#include <iostream>
#include "primitives.h"

Square::Square(float x, float width) {

    this->x = x;
    //this->y = y;
    this->width = width;
    //this->height = height;

	Square::create();
}

Square::~Square() {

}

void Square::create() {
    float vertices[] = {
        x,  0.5f, 0.0f,  // top right
        x, -0.5f, 0.0f,  // bottom right
        x - width, -0.5f, 0.0f,  // bottom left
        x - width,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[]{
        0, 1, 3,
        1, 2, 3
    };
    unsigned int vertexCount{ 4 };
    unsigned int indicesCount{ 6 };

    vb = new VertexBuffer(vertices, vertexCount);
    eb = new IndexBuffer(indices, indicesCount);
}

void Square::draw() {
    vb->bind();
    eb->draw();
}