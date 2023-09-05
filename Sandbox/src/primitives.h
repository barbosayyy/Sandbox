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

    virtual void draw();

    // Change this definition if matrices transform unexpectedly
    void setPosition(float x, float y, float z);
    void setPosition(glm::vec3 position);
    
    void setRotation(float degrees, glm::vec3 axis, GLboolean set_by_degrees);
    
    void setScale(float x, float y, float z);
    void setScale(glm::vec3 scale);
    
    glm::vec3 getPosition();
    glm::mat4 getModelMatrix();

    std::vector<unsigned int> texture;
protected:
    glm::mat4 ml_matrix;
    glm::mat4 translationM;
    glm::mat4 rotationM;
    glm::mat4 scaleM;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    VertexBuffer* vb;
    IndexBuffer* eb;

    virtual void create();
};

class Square : public Primitive{
public:
    Square(float x, float y, float z);
    ~Square();

    void draw() override;
protected:
    void create() override;
};

class Cube : public Primitive {
public:
    Cube(float x, float y, float z);
    ~Cube();

    void draw() override;
private:
    void create() override;
};

class Square2 : public Primitive {
public:
    Square2(float x, float y, float z);
    ~Square2();

    void draw() override;
private:
    void create() override;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};
