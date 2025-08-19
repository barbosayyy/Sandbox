#pragma once

#include "Core/Base.h"
#include "ECS/ComponentManager.h"
#include "ECS/Components.h"

#include <unordered_map>
#include <bitset>

namespace Sb {
    class Scene{
    public:
        Scene();
        ~Scene();

        u32 AddEntity();
        void RemoveEntity(u32 entityID);

        template <typename T>
        void AddEntityComponent(u32 entityID) { _componentManager.AddComponent<T>(entityID); };

        template <typename T>
        void RemoveEntityComponent(u32 entityID) { _componentManager.AddComponent<T>(entityID); };

    private:
        u32 _nextEntityId;
        ComponentManager<
        DummyComponent,
        TransformComponent,
        RendererComponent
        > _componentManager;
    };
}
