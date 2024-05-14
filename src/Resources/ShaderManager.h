#include "../Core/Singleton.h"
#include "../Renderer/Shader.h"
#include "ResourceManager.h"

namespace Sandbox{
    class ShaderManager : public ResourceManager{
    public:
        ShaderManager();
        ~ShaderManager();
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