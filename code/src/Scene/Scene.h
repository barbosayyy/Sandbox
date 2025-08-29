#pragma once

#include "Core/Base.h"
#include "ECS/ComponentManager.h"
#include "ECS/Components.h"

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

#ifdef SB_DEBUG
        template<typename T>
        std::vector<T> GetComponentDense() const { return _componentManager.GetComponentStoreDense<T>(); }
        template<typename T>
        std::vector<u32> GetComponentSparse() const { return _componentManager.GetComponentStoreSparse<T>(); }
        template<typename T>
        SparseSet<T> GetComponentSparseSet() const { return _componentManager.GetSparseSet<T>(); }
#endif

    private:
        u32 _nextEntityId;
        ComponentManager<
        DummyComponent,
        TransformComponent,
        RendererComponent
        > _componentManager;
    };
}
