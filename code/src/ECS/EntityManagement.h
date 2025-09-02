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
#ifdef SB_DEBUG
    template<typename T>
    static void PrintComponentStore() { ECS::Registry::GetInstance().GetComponentSparseSet<T>().PrintDenseSize(); ECS::Registry::GetInstance().GetComponentSparseSet<T>().PrintSparse(); }
#endif
}