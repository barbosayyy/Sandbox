#pragma once
#include "Rendering/VertexBuffer.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/Material.h"
#include "Rendering/Renderer.h"
#include "Resources/ShaderManager.h"
#include "Rendering/Texture.h"

#include <cstddef>

namespace SbEngine{
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
        
        glm::vec3 GetPosition() const ;
        glm::mat4 GetModelMatrix() const ;

        void RequestShader(int shaderVertexRID, int shaderFragmentRID, ShaderManager& shaderManager);
        void ReleaseShader(int shaderVertexRID, int shaderFragmentRID, ShaderManager& shaderManager);
        size_t GetShadersAmount() const {return _mat.shaders.size();};

        Material& GetMaterial() {return this->_mat;};

        virtual void Draw(Renderer* renderer) = 0;

    protected:
        glm::mat4 _mLmatrix;
        glm::mat4 _translationM;
        glm::mat4 _rotationM;
        glm::mat4 _scaleM;

        glm::vec3 _position;
        glm::vec3 _rotation;
        glm::vec3 _scale;

        VertexBuffer* _vb;
        IndexBuffer* _eb;

        Material _mat;

        virtual void Create() = 0;
    };
}

