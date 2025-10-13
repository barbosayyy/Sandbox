#pragma once

#include "RenderPass.h"

namespace Sb {
    class GeometryPass final : public RenderPass{
    public:
        void Execute() override;
    private:
    };
}