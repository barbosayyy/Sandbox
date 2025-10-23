#include "Components.h"
#include "Registry.h"
#include "ECS/EntityManagement.h"

namespace Sb {
    void HierarchyComponent::AddChild(u32 entityID) {
        ECS::Registry& reg = ECS::Registry::GetInstance();
        
        // Add hierarchy component to target entity if it has none
        if(!reg.GetComponentSparseSet<HierarchyComponent>().Contains(entityID)) {
            AddEntityComponent<HierarchyComponent>(entityID);
        }
        
        if(std::find(this->children.begin(), this->children.end(), entityID) != this->children.end()){
            this->children.push_back(entityID);
        }
        GetEntityComponent<HierarchyComponent>(entityID).parent = this->sparseIndex;
        Log::Print("ECS: Added child ", entityID, " to parent ", this->sparseIndex);
    };
    
    void HierarchyComponent::SetParent(u32 entityID) {
        ECS::Registry& reg = ECS::Registry::GetInstance();
        
        // Add hierarchy component to target entity if it has none
        if(!reg.GetComponentSparseSet<HierarchyComponent>().Contains(entityID)) {
            AddEntityComponent<HierarchyComponent>(entityID);
        }
        
        this->parent = entityID;
        HierarchyComponent& comp = GetEntityComponent<HierarchyComponent>(entityID);
        if(std::find(comp.children.begin(), comp.children.end(), this->sparseIndex) != comp.children.end()) {
            comp.children.push_back(this->sparseIndex);
            Log::Print("ECS: Added parent ", entityID, " to child ", this->sparseIndex);
        }
    }
}