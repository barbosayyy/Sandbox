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
        std::vector<vec3> lightPos;
	    std::vector<vec3> lightCol;
        int numLights;
        bool init = false;
    };
}