#pragma once

#include <vector>
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "shaders.h"
#include "texture.h"
#include "glm.hpp"

class Primitive {
public:
    Primitive();
    ~Primitive();

    void setPosition(float x, float y);
    void setRotation(float degrees, glm::vec3 axis, GLboolean set_by_degrees);
    glm::mat4 getPosition();
    std::vector<unsigned int> texture;

    virtual void draw();
protected:
    glm::mat4 ml_matrix;
    float x;
    float y;
    float width;
    float height;

    VertexBuffer* vb = nullptr;
    IndexBuffer* eb = nullptr;

    virtual void create();
};

class Square : public Primitive{
public:
    Square(float x, float y);
    ~Square();

    void draw() override;
protected:
    void create() override;
};


class Cube : public Primitive {
public:
    Cube(float x, float y);
    ~Cube();

    void draw() override;
private:
    void create() override;
};
