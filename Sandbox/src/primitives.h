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

    // Change this definition if matrices transform unexpectedly
    void setPosition(float x, float y);
    void setRotation(float degrees, glm::vec3 axis, GLboolean set_by_degrees);
    glm::vec3 getPosition();
    glm::mat4 getModelMatrix();
    std::vector<unsigned int> texture;

    virtual void draw();
protected:
    glm::mat4 ml_matrix;
    glm::vec3 position;
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
    unsigned int texture1;
    unsigned int texture2;
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

class Square2 : public Primitive {
public:
    Square2(float x, float y);
    ~Square2();

    void draw() override;
private:
    void create() override;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};
