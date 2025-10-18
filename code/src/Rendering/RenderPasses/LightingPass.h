#pragma once

#include "RenderPass.h"
#include "Rendering/Shader.h"

namespace Sb {
    class LightingPass final : public RenderPass{
    public:
        LightingPass();
        void Execute() final override;
    private:
        Shader* lightingPassShader;
        bool init = false;
    };
}