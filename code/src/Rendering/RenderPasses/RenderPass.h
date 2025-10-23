#pragma once

namespace Sb {
    class RenderPass {
    public:
        virtual ~RenderPass() = default;
        virtual void Execute() = 0;
    private:
    };
}