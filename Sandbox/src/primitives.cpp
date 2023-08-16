
#include "primitives.h"

Square::Square(float x, float width) {

    this->x = x;
    //this->y = y;
    this->width = width;
    //this->height = height;

	Square::create();
}

Square::~Square() {
    delete(vb);
    delete(eb);
}

void Square::create() {
    float vertices[] = {
        // positions          // color            // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[]{
        0, 1, 3,
        1, 2, 3
    };

    unsigned int nOfAttrib{ 3 };
    unsigned int vertexCount{ 4*nOfAttrib };
    unsigned int indicesCount{ 6 };

    vb = new VertexBuffer(vertices, vertexCount);
    eb = new IndexBuffer(indices, indicesCount);
}

void Square::draw() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    vb->bind();
    eb->draw();
}