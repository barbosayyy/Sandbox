#pragma once

#include "vertex_buffer.h"
#include "index_buffer.h"

class Square {
public:
    Square(float x, float width);
    ~Square();

    void draw();

    float x;
    float y;
    float width;
    float height;
private:
    VertexBuffer* vb;
    IndexBuffer* eb;

    void create();
};