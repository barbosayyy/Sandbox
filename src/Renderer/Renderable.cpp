#include "Renderable.h"
#include "../Core/Debug.h"
#include "Texture.h"

using namespace Sandbox;

Renderable::Renderable() : 
    _mLmatrix{glm::mat4(1.0)}, 
    _translationM{ glm::mat4(1.0)},
    _rotationM{ glm::mat4(1.0)},
    _scaleM{ glm::mat4(1.0)},
    _position{0.0f},
    _rotation{0.0f},
    _scale{0.0f},
    _vb{nullptr},
    _eb{nullptr},
    _mat{
        std::vector<unsigned int>{},
        std::vector<Shader*>{},
        0,
        0,
        vec4{0.0f,0.0f,0.0f,1.0f}}
{
    Renderable::SetPosition(0.0f,0.0f,0.0f);
}

Renderable::Renderable(float x, float y, float z) : 
    _mLmatrix{glm::mat4(1.0)}, 
    _translationM{ glm::mat4(1.0)},
    _rotationM{ glm::mat4(1.0)},
    _scaleM{ glm::mat4(1.0)},
    _position{0.0f},
    _rotation{0.0f},
    _scale{0.0f},
    _vb{nullptr},
    _eb{nullptr},
    _mat{
        std::vector<unsigned int>{},
        std::vector<Shader*>{},
        0,
        0,
        vec4{0.0f,0.0f,0.0f,1.0f}}
{
    Renderable::SetPosition(x,y,z);
}

Renderable::~Renderable()
{
    _mat.shaders.clear();

    if (_vb != nullptr)
    {
        delete(_vb);
    }

    if (_eb != nullptr)
    {
        delete(_eb);
    }
}

void Renderable::SetPosition(float x, float y, float z)
{
    this->_translationM = glm::mat4(1.0f);
    this->_position.x = x;
    this->_position.y = y;
    this->_position.z = z;

    _translationM = glm::translate(_translationM, _position);
    _mLmatrix = _translationM * _rotationM * _scaleM;
}

void Renderable::SetPosition(glm::vec3 position)
{
    this->_translationM = glm::mat4(1.0f);
    this->_position = position;
    _translationM = glm::translate(_translationM, _position);
    _mLmatrix = _translationM * _rotationM * _scaleM;
}

void Renderable::SetRotation(float value, glm::vec3 axis, GLboolean setByDegrees)
{
    _rotationM = glm::mat4(1.0f);
    _rotation = glm::vec3(value*axis.x, value*axis.y, value*axis.z);
    
    if (setByDegrees == GL_TRUE)
    {
        _rotationM =glm::rotate(_rotationM, glm::radians(value), _rotation);
    }
    else
    {
        _rotationM = glm::rotate(_rotationM, value, _rotation);
    }
    _mLmatrix = _translationM * _rotationM * _scaleM;
}

void Renderable::SetScale(float x, float y, float z)
{
    _scaleM = glm::mat4(1.0f);
    this->_scale.x = x;
    this->_scale.y = y;
    this->_scale.z = z;

    _scaleM = glm::scale(_scaleM, _scale);
    _mLmatrix = _translationM * _rotationM * _scaleM;
}

void Renderable::SetScale(glm::vec3 scale)
{
    _scaleM = glm::mat4(1.0f);
    this->_scale = scale;

    _scaleM = glm::scale(_scaleM, scale);
    _mLmatrix = _translationM * _rotationM * _scaleM;
}

void Renderable::Create()
{

}

glm::vec3 Renderable::GetPosition()
{
    return _position;
}

glm::mat4 Renderable::GetModelMatrix()
{
    return _mLmatrix;
}

void Renderable::RequestShader(int shaderVertexRID, int shaderFragmentRID, ShaderManager& shaderManager)
{
    Shader* pSh = shaderManager.GetShader(shaderVertexRID, shaderFragmentRID);
    if(pSh != nullptr){
        pSh->Use();
        pSh->SetInt("material.diffuse", 0);
        pSh->SetInt("material.specular", 1);
        pSh->SetInt("material.emissive", 2);
        this->_mat.shaders.push_back(pSh);
    }
    else{
        Logger::Trace(LogLevel::WARNING, "Failed to retrieve pointer to shader of ID: ", shaderVertexRID, " ", shaderFragmentRID);
    }
}

void Renderable::Draw(Renderer* renderer)
{
    if(this->_mat.shaders.size() > 0){
        for(Shader* shader : this->_mat.shaders){
            if(shader != nullptr){
                shader->Use();
                shader->SetMat4("view", renderer->GetRenderCamera()->GetView());
                shader->SetMat4("projection", renderer->GetProjection());
                
                shader->SetFloat("material.shininess", _mat.roughnessStrength);
                shader->SetFloat("material.emissiveStrength", _mat.emissiveStrength);
                shader->SetVec4("material.col", _mat.colorOverlay.r, _mat.colorOverlay.g, _mat.colorOverlay.b, _mat.colorOverlay.a);

                // TEMP
                // TODO: REMOVE
                //  TEST LIGHTING INFO

                    vec3 lightColor(1.0f, 1.0f, 1.0f);
                    float spotlightInnerRadius{8.0f};
                    float spotlightOuterRadius{8.0f};
                    vec3 pointLightPositions[] =
                    {
                       vec3(0.5f, 0.0f, 0.0f)
                    };

                    shader->SetVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
                    shader->SetVec3("spotLight.diffuse", 0.7f, 0.7f, 0.7f);
                    shader->SetVec3("spotLight.specular", 0.0f, 0.0f, 0.0f);
                    shader->SetFloat("spotLight.constant", 1.0f);
                    shader->SetFloat("spotLight.linear", 0.09f);
                    shader->SetFloat("spotLight.quadratic", 0.032f);
                    shader->SetVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
                    shader->SetVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
                    shader->SetVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
                    shader->SetVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
                    shader->SetVec3("pointLight[0].position", pointLightPositions[0]);
                    shader->SetVec3("pointLight[0].ambient", 0.5f, 0.5f, 0.5f);
                    shader->SetVec3("pointLight[0].diffuse", 0.8f, 0.8f, 0.8f);
                    shader->SetVec3("pointLight[0].specular", 1.0f, 1.0f, 1.0f);
                    shader->SetFloat("pointLight[0].constant", 1.0f);
                    shader->SetFloat("pointLight[0].linear", 0.09f);
                    shader->SetFloat("pointLight[0].quadratic", 0.032f);
                    shader->SetVec3("spotLight.direction", renderer->GetRenderCamera()->_front);
                    shader->SetVec3("spotLight.position", renderer->GetRenderCamera()->_position);
                    shader->SetFloat("spotLight.innerRadius", glm::cos(glm::radians(spotlightInnerRadius)));
                    shader->SetFloat("spotLight.outerRadius", glm::cos(glm::radians(spotlightOuterRadius)));
            
                shader->SetVec3("viewer.position", renderer->GetRenderCamera()->_position.x, renderer->GetRenderCamera()->_position.y, renderer->GetRenderCamera()->_position.z);
            
                // TODO: Apply inverse transponse only when detecting changes in position rotation and scale
                mat4 normal{glm::inverseTranspose(this->GetModelMatrix())};
                normal = glm::inverseTranspose(this->GetModelMatrix());
		        shader->SetMat4("normalInverse", normal);
		        shader->SetMat4("model", this->GetModelMatrix());
            }
        }
    }
    u8 i = 0;
    if (this->_mat.textures.size() > 0){
        for (unsigned int tex : this->_mat.textures)
        {
            glActiveTexture(textureUnitMap.at(i));
            glBindTexture(GL_TEXTURE_2D, this->_mat.textures.at(i));
            i++;
        }
    }
    else{
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 1);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, 2);
    }

    if(_vb != nullptr){
        _vb->Bind();
        if(_eb == nullptr)
            _vb->Draw();
    }
    if(_eb != nullptr){
        _eb->Draw();
    }
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}
