#pragma once

#include "RenderPass.h"
#include "Rendering/Shader.h"

namespace Sb {
    class SkyboxPass final : public RenderPass{
    public:
        void Execute() final override;
    };
}