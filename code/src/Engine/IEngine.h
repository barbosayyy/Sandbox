#pragma once

#include "Core/Base.h"
#include "Core/Config.h"
#include "Rendering/Renderer.h"
#include "Input/Input.h"

namespace SbEngine{
    class IEngine {
    protected:
        IEngine() = default;
        struct Stats{
            float fps;
            float deltaTime;
            float elapsedTime;
        };

    public:
        virtual ~IEngine() = default;
        virtual Renderer& GetRenderer() const = 0;
        virtual InputManager& GetInputManager() const = 0;
        // Returns internal structure containing engine stats
        virtual Stats GetStats() const = 0;
        virtual Config GetConfig() const = 0;
    };

}
