#include "Primitives.h"
#include "../Core/Debug.h"

using namespace Sandbox;

Primitive::Primitive() : 
    _mLmatrix{glm::mat4(1.0)}, 
    _translationM{ glm::mat4(1.0)},
    _rotationM{ glm::mat4(1.0)},
    _scaleM{ glm::mat4(1.0)},
    _position{0.0f},
    _rotation{0.0f},
    _scale{0.0f},
    _vb{nullptr},
    _eb{nullptr}
{
}

Primitive::~Primitive()
{
    if (_vb != nullptr)
    {
        delete(_vb);
    }

    if (_eb != nullptr)
    {
        delete(_eb);
    }
}

void Primitive::SetPosition(float x, float y, float z)
{
    this->_translationM = glm::mat4(1.0f);
    this->_position.x = x;
    this->_position.y = y;
    this->_position.z = z;

    _translationM = glm::translate(_translationM, _position);
    _mLmatrix = _translationM * _rotationM * _scaleM;
}

void Primitive::SetPosition(glm::vec3 position)
{
    this->_translationM = glm::mat4(1.0f);
    this->_position = position;
    _translationM = glm::translate(_translationM, _position);
    _mLmatrix = _translationM * _rotationM * _scaleM;
}

void Primitive::SetRotation(float value, glm::vec3 axis, GLboolean set_by_degrees)
{
    _rotationM = glm::mat4(1.0f);
    _rotation = glm::vec3(value*axis.x, value*axis.y, value*axis.z);
    
    if (set_by_degrees == GL_TRUE)
    {
        _rotationM =glm::rotate(_rotationM, glm::radians(value), _rotation);
    }
    else
    {
        _rotationM = glm::rotate(_rotationM, value, _rotation);
    }
    _mLmatrix = _translationM * _rotationM * _scaleM;
}

void Primitive::SetScale(float x, float y, float z)
{
    _scaleM = glm::mat4(1.0f);
    this->_scale.x = x;
    this->_scale.y = y;
    this->_scale.z = z;

    _scaleM = glm::scale(_scaleM, _scale);
    _mLmatrix = _translationM * _rotationM * _scaleM;
}

void Primitive::SetScale(glm::vec3 scale)
{
    _scaleM = glm::mat4(1.0f);
    this->_scale = scale;

    _scaleM = glm::scale(_scaleM, scale);
    _mLmatrix = _translationM * _rotationM * _scaleM;
}

void Primitive::Draw()
{

}

void Primitive::Create()
{

}

glm::vec3 Primitive::GetPosition()
{
    return _position;
}

glm::mat4 Primitive::GetModelMatrix()
{
    return _mLmatrix;
}

void Primitive::RequestShader(int shaderVertexRID, int shaderFragmentRID, ShaderManager& shaderManager)
{
    Shader* pSh = shaderManager.GetShader(shaderVertexRID, shaderFragmentRID);
    if(pSh != nullptr){
        this->_mat._shaders.push_back(pSh);
    }
    else{
        Logger::Trace(LogLevel::WARNING, "Failed to retrieve pointer to shader of ID: ", shaderVertexRID, " ", shaderFragmentRID);
    }
}

//

Square::Square(float x, float y, float z)
{
    Square::Create();
    Square::SetPosition(x, y, z);
}

Square::~Square() {
    
}

void Square::Create(){
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

    _vb = new VertexBuffer(vertices, vertexCount*nOfAttrib);
    _eb = new IndexBuffer(indices, indicesCount);
}

void Square::Draw() {
    if(this->_mat._texture.size() > 1){
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, this->texture.at(0));
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, this->texture.at(1));
    }
    _vb->Bind();
    _eb->Draw();
}

//

Cube::Cube(float x, float y, float z)
{
    Cube::Create();
    Cube::SetPosition(x, y, z);
}

Cube::Cube()
{
    Cube::Create();
    Cube::SetPosition(0.0f, 0.0f, 0.0f);
}

Cube::~Cube()
{

}

void Cube::Create()
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
    _vb = new VertexBuffer(vertices, vertexCount);
    //eb = new IndexBuffer(indices, indicesCount);
}

void Cube::Draw()
{
    //if (this->texture.size() > 1)
    //    glActiveTexture(GL_TEXTURE0);
    //    glBindTexture(GL_TEXTURE_2D, this->texture.at(0));
    //
    int i = 0;
    if (this->_mat._texture.size() > 0)
        for (unsigned int tex : this->_mat._texture)
        {
            glActiveTexture(Resources::_textureUnitMap.at(i));
            glBindTexture(GL_TEXTURE_2D, this->_mat._texture.at(i));
            i++;
        }

    _vb->Bind();
    _vb->Draw();
}

//

Square2::Square2(float x, float y, float z)
{
    Create();
    SetPosition(x, y, z);
}

Square2::~Square2()
{

}

void Square2::Create()
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

    _vb = new VertexBuffer(vertices, vertexCount*nOfAttrib);
    _eb = new IndexBuffer(indices, indicesCount);
}

void Square2::Draw()
{
    _vb->Bind();
    _eb->Draw();
}