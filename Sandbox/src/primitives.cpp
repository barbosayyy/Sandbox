
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

void Primitive::setPosition(float x, float y, float z)
{
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
    glm::mat4 mat = glm::mat4(1.0);
    ml_matrix = glm::translate(mat, glm::vec3(this->position.x, this->position.y, this->position.z));
}

void Primitive::setPosition(glm::vec3 position)
{
    this->position += position;
    glm::mat4 mat = glm::mat4(1.0);
    ml_matrix = glm::translate(mat, this->position);
}

void Primitive::setRotation(float value, glm::vec3 axis, GLboolean set_by_degrees)
{
    glm::mat4 mat = glm::mat4(1.0);
    mat = glm::translate(mat, position);
    mat = glm::scale(mat, scale);
    if (set_by_degrees == GL_TRUE)
    {
        ml_matrix = glm::rotate(mat, glm::radians(value), axis);
    }
    else
    {
        ml_matrix = glm::rotate(mat, value, axis);
    }
}

void Primitive::setScale(float x, float y, float z)
{
    glm::mat4 mat = glm::mat4(1.0);
    this->scale.x = x;
    this->scale.y = y;
    this->scale.z = z;
    ml_matrix = glm::scale(mat, scale);
}

void Primitive::setScale(glm::vec3 scale)
{
    this->scale = scale;
    glm::mat4 mat = glm::mat4(1.0);
    ml_matrix = glm::scale(mat, scale);
}

void Primitive::draw()
{

}

void Primitive::create()
{

}

glm::vec3 Primitive::getPosition()
{
    return position;
}

glm::mat4 Primitive::getModelMatrix()
{
    return ml_matrix;
}

//

Square::Square(float x, float y, float z)
{
    Square::create();
    Square::setPosition(x, y, z);
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

Cube::Cube(float x, float y, float z)
{
    Cube::create();
    Cube::setPosition(x, y, z);
}

Cube::~Cube()
{

}

void Cube::create()
{
    //TODO:
    //  Add texcoords to vertices and add that to vertex attrib pointer
    //

    float vertices[] = {
        //pos                 //normal
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    unsigned int vertexCount{ 36 };
    vb = new VertexBuffer(vertices, vertexCount);
    //eb = new IndexBuffer(indices, indicesCount);
}

void Cube::draw()
{
    vb->bind();
    vb->draw();
}

//

Square2::Square2(float x, float y, float z)
{
    create();
    setPosition(x, y, z);
}

Square2::~Square2()
{

}

void Square2::create()
{
    float vertices[] = {
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int nOfAttrib{ 2 };
    unsigned int vertexCount{ 4 };
    unsigned int indicesCount{ 6 };

    vb = new VertexBuffer(vertices, vertexCount*nOfAttrib);
    eb = new IndexBuffer(indices, indicesCount);
}

void Square2::draw()
{
    vb->bind();
    eb->draw();
}