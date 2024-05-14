#pragma once

#include <vector>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "../Core/Utils.h"
#include "../Resources/ShaderManager.h"
#include "Material.h"

namespace Sandbox{
    class Primitive {
    public:
        Primitive();
        ~Primitive();

        virtual void Draw();

        // Change this definition if matrices transform unexpectedly
        void SetPosition(float x, float y, float z);
        void SetPosition(glm::vec3 position);
        
        void SetRotation(float degrees, glm::vec3 axis, GLboolean Set_by_degrees);
        
        void SetScale(float x, float y, float z);
        void SetScale(glm::vec3 scale);
        
        glm::vec3 GetPosition();
        glm::mat4 GetModelMatrix();
        Material _mat;

        void RequestShader(int shaderVertexRID, int shaderFragmentRID, ShaderManager& shaderManager);
        void ReleaseShader(int shaderVertexRID, int shaderFragmentRID, ShaderManager& shaderManager);
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

        virtual void Create();
    };

    class Square : public Primitive{
    public:
        Square(float x, float y, float z);
        ~Square();

        void Draw() override;
    protected:
        void Create() override;
    };

    class Cube : public Primitive {
    public:
        Cube(float x, float y, float z);
        Cube();

        ~Cube();

        void Draw() override;
    private:
        void Create() override;
    };

    class Square2 : public Primitive {
    public:
        Square2(float x, float y, float z);
        ~Square2();

        void Draw() override;
    private:
        void Create() override;
        std::vector<float> _vertices;
        std::vector<unsigned int> _indices;
    };
}

