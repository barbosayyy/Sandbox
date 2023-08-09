#pragma once

#include "vertex_buffer.h"

class Triangle {
public:
    Triangle();
    ~Triangle();

    void draw();
private:
    VertexBuffer* vb;

    void create();
};