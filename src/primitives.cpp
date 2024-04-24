#include "primitives.h"

using namespace Sandbox;

Primitive::Primitive() : 
    ml_matrix{glm::mat4(1.0)}, 
    translationM{ glm::mat4(1.0)},
    rotationM{ glm::mat4(1.0)},
    scaleM{ glm::mat4(1.0)},
    position{0.0f},
    rotation{0.0f},
    scale{0.0f},
    vb{nullptr},
    eb{nullptr}
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
    translationM = glm::mat4(1.0f);
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;

    translationM = glm::translate(translationM, position);
    ml_matrix = translationM * rotationM * scaleM;
}

void Primitive::setPosition(glm::vec3 position)
{
    translationM = glm::mat4(1.0f);
    this->position = position;
    translationM = glm::translate(translationM, position);
    ml_matrix = translationM * rotationM * scaleM;
}

void Primitive::setRotation(float value, glm::vec3 axis, GLboolean set_by_degrees)
{
    rotationM = glm::mat4(1.0f);
    rotation = glm::vec3(value*axis.x, value*axis.y, value*axis.z);
    
    if (set_by_degrees == GL_TRUE)
    {
        rotationM =glm::rotate(rotationM, glm::radians(value), rotation);
    }
    else
    {
        rotationM = glm::rotate(rotationM, value, rotation);
    }
    ml_matrix = translationM * rotationM * scaleM;
}

void Primitive::setScale(float x, float y, float z)
{
    scaleM = glm::mat4(1.0f);
    this->scale.x = x;
    this->scale.y = y;
    this->scale.z = z;

    scaleM = glm::scale(scaleM, scale);
    ml_matrix = translationM * rotationM * scaleM;
}

void Primitive::setScale(glm::vec3 scale)
{
    scaleM = glm::mat4(1.0f);
    this->scale = scale;

    scaleM = glm::scale(scaleM, scale);
    ml_matrix = translationM * rotationM * scaleM;
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
        /*
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
        */
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f,  0.0f
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
    if(this->texture.size() > 1)
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, this->texture.at(0));
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, this->texture.at(1));

    vb->bind();
    eb->draw();
}

//

Cube::Cube(float x, float y, float z)
{
    Cube::create();
    Cube::setPosition(x, y, z);
}

Cube::Cube()
{
    Cube::create();
    Cube::setPosition(0.0f, 0.0f, 0.0f);
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
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };
    unsigned int vertexCount{ 36 };
    vb = new VertexBuffer(vertices, vertexCount);
    //eb = new IndexBuffer(indices, indicesCount);
}

void Cube::draw()
{
    //if (this->texture.size() > 1)
    //    glActiveTexture(GL_TEXTURE0);
    //    glBindTexture(GL_TEXTURE_2D, this->texture.at(0));
    //
    int i = 0;
    if (this->texture.size() > 0)
        for (unsigned int tex : this->texture)
        {
            glActiveTexture(Resources::TextureUnitMap.at(i));
            glBindTexture(GL_TEXTURE_2D, this->texture.at(i));
            i++;
        }

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