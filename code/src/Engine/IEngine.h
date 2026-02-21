#pragma once

#include "Core/Base.h"
#include "Core/Config.h"
#include "Client/IClient.h"
#include "Rendering/Renderer.h"
#include "Input/Input.h"
#include "ECS/Registry.h"
#include "Resources/ResourceManager.h"

namespace Sb {
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
        virtual void InitContext(const String& name, IClient& client) = 0;
        virtual Renderer& GetRenderer() const = 0;
        virtual InputManager& GetInputManager() const = 0;
        virtual ECS::Registry& GetECSRegistry() const = 0;
        virtual ResourceManagement::ResourceManager& GetResourceManager() const = 0;
        // Returns internal structure containing engine stats
        virtual void SetUIRendering(bool enable) = 0;
        virtual Stats GetStats() const = 0;
        virtual Config GetConfig() const = 0;
    };
}
