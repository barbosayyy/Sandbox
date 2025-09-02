#include "ECS/EntityManagement.h"
#include "ECS/Components.h"

namespace Sb {
    u32 AddEntity() {
        ECS::Registry& registryInstance = ECS::Registry::GetInstance();
        registryInstance.AddComponent<DummyComponent>(registryInstance.GetNextEntityID());
        registryInstance.IncrementNextEntityID();
        return registryInstance.GetNextEntityID()-1;
    }
    
    void RemoveEntity(u32 entityID) {
        ECS::Registry::GetInstance().RemoveAllComponents(entityID);
    }
}
