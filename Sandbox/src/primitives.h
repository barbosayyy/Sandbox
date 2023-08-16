#pragma once

#include "vertex_buffer.h"
#include "index_buffer.h"
#include "shaders.h"
#include "texture.h"

class Square {
public:
    Square(float x, float width);
    ~Square();

    void draw();

    float x;
    float y;
    float width;
    float height;
    unsigned int texture;
private:
    VertexBuffer* vb;
    IndexBuffer* eb;

    void create();
};