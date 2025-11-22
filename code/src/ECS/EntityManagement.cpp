#include "ECS/EntityManagement.h"
#include "Core/Types.h"
#include "ECS/Components.h"

namespace Sb {
    u32 AddEntity() {
        ECS::Registry& reg = ECS::Registry::GetInstance();
        reg.AddComponent<DummyComponent>(reg.GetNextEntityID());
        reg.IncrementNextEntityID();
        return reg.GetNextEntityID()-1;
    }

    u32 LoadEntity(SbGUID entityGUID) {
        ECS::Registry& reg = ECS::Registry::GetInstance();
        Entity newEnt = AddEntity();
        reg.EmplaceEntityGUID(entityGUID, newEnt);
        return newEnt;
    }
    
    void RemoveEntity(u32 entityID) {
        ECS::Registry::GetInstance().RemoveAllComponents(entityID);
    }
}
