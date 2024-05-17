#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Material.h"

#include "../Resources/ShaderManager.h"
#include "Renderer.h"
#include "Texture.h"

namespace Sandbox{
    class Renderable {
    public:
        Renderable();
        Renderable(float x, float y, float z);
        ~Renderable();

        // Change this definition if matrices transform unexpectedly
        void SetPosition(float x, float y, float z);
        void SetPosition(glm::vec3 position);
        
        void SetRotation(float degrees, glm::vec3 axis, GLboolean setByDegrees);
        
        void SetScale(float x, float y, float z);
        void SetScale(glm::vec3 scale);
        
        glm::vec3 GetPosition();
        glm::mat4 GetModelMatrix();

        void RequestShader(int shaderVertexRID, int shaderFragmentRID, ShaderManager& shaderManager);
        void ReleaseShader(int shaderVertexRID, int shaderFragmentRID, ShaderManager& shaderManager);
        
        Material GetMaterial() {return _mat;};

        void AddMatTexture(Texture& tex) {this->_mat.textures.push_back(tex._texture);};

        void SetMatEm(u32 param) {this->_mat.emissiveStrength = param;};
        void SetMatRough(u32 param) {this->_mat.roughnessStrength = param;};

        void SetMatColor(vec4 color) {this->_mat.colorOverlay = color;};
        void SetMatColor(float x, float y, float z, float a) {this->_mat.colorOverlay = vec4(x,y,z,a);};
        void SetMatColor(float x, float y, float z) {this->_mat.colorOverlay = vec4(x,y,z,this->_mat.colorOverlay.a);};

        virtual void Draw(Renderer* renderer) = 0;

    protected:
        glm::mat4 _mLmatrix;
        glm::mat4 _translationM;
        glm::mat4 _rotationM;
        glm::mat4 _scaleM;

        glm::vec3 _position;
        glm::vec3 _rotation;
        glm::vec3 _scale;

        Material _mat;

        VertexBuffer* _vb;
        IndexBuffer* _eb;

        virtual void Create() = 0;
    };
}

