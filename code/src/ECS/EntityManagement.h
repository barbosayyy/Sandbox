#pragma once

#include "Core/Base.h"
#include "ECS/Registry.h"

namespace Sb {
    u32 AddEntity();
    void RemoveEntity(u32 entityID);
    template<typename T>
    static void AddEntityComponent(u32 entityID) { ECS::Registry::GetInstance().AddComponent<T>(entityID); }
    template<typename T>
    static void RemoveEntityComponent(u32 entityID) { ECS::Registry::GetInstance().RemoveComponent<T>(entityID); }
    template<typename T>
    static T& GetEntityComponent(u32 entityID) { return ECS::Registry::GetInstance().GetComponent<T>(entityID); }
#ifdef SB_BUILD_DEBUG
    template<typename T>
    static void PrintComponentStore() { ECS::Registry::GetInstance().GetComponentSparseSet<T>().PrintDenseSize(); ECS::Registry::GetInstance().GetComponentSparseSet<T>().PrintSparse(); }
#endif
}