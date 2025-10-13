#pragma once

namespace Sb {
    class RenderPass {
    public:
        RenderPass() = default;
        ~RenderPass() = default;
        virtual void Execute() = 0;
    private:
    };
}