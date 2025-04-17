#pragma once

#include "Core/Singleton.h"
#include "Rendering/Shader.h"
#include "Resources/ResourceManager.h"

namespace SbEngine{
    class ShaderManager : public ResourceManager{
    public:
        ShaderManager();
        ~ShaderManager();
        void Init() override;
        Shader* GetShader(int vRId, int fRId);
        Shader* NewShader(int vRId, int fRId);
        void RemoveShader(int pos);
        
        size_t _shaderCount;
    private:
        // replace with a pool allocator
        std::vector<Shader*> _shaders;
        std::vector<ShaderData> _shaderData;
        Shader* _defaultShader;
    };
}