
#include "primitives.h"

Primitive::Primitive()
{

}

Primitive::~Primitive()
{
    if (vb != nullptr)
    {
        delete(vb);
    }

    if (eb != nullptr)
    {
        delete(eb);
    }
}

void Primitive::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
    ml_matrix = glm::mat4(1.0f);
    ml_matrix = glm::translate(ml_matrix, glm::vec3(x, y, 0.0f));
}

void Primitive::setRotation(float value, glm::vec3 axis, GLboolean set_by_degrees)
{
    glm::mat4 mat = glm::mat4(1.0);
    mat = glm::translate(mat, glm::vec3(x, y, 0.0));
    if (set_by_degrees == GL_TRUE)
    {

        mat = glm::rotate(mat, glm::radians(value), axis);
    }
    else
    {
        mat = glm::rotate(mat, value, axis);
    }
    ml_matrix = mat;
}

void Primitive::draw()
{

}

void Primitive::create()
{

}

glm::mat4 Primitive::getPosition()
{
    return ml_matrix;
}

//

Square::Square(float x, float y)
{
    Square::create();
    Square::setPosition(x, y);
}

Square::~Square() {
    
    
}

void Square::create(){
    float vertices[] = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[]{
        0, 1, 3,
        1, 2, 3
    };

    unsigned int nOfAttrib{ 2 };
    unsigned int vertexCount{ 4 };
    unsigned int indicesCount{ 6 };

    vb = new VertexBuffer(vertices, vertexCount*nOfAttrib);
    eb = new IndexBuffer(indices, indicesCount);
}

void Square::draw() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture.at(0));
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, this->texture.at(1));
    vb->bind();
    eb->draw();
}

//

Cube::Cube(float x, float y)
{
    Cube::create();
    Cube::setPosition(x, y);
}

Cube::~Cube()
{

}

void Cube::create()
{
    float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f
    };
    unsigned int nOfAttrib{ 2 };
    unsigned int vertexCount{ 36 };
    vb = new VertexBuffer(vertices, vertexCount);
    //eb = new IndexBuffer(indices, indicesCount);
}

void Cube::draw()
{
    vb->bind();
    vb->draw();
}

