#include "Components.h"
#include "Registry.h"
#include "ECS/EntityManagement.h"

namespace Sb {
    void HierarchyComponent::AddChild(u32 entityID) {
        ECS::Registry& reg = ECS::Registry::GetInstance();
        
        u32 unmovedIndex = this->GetSparseIndex();

        // Add hierarchy component to target entity if it has none
        if(!reg.GetComponentSparseSet<HierarchyComponent>().Contains(entityID)) {
            AddEntityComponent<HierarchyComponent>(entityID);
        }

        HierarchyComponent& current = GetEntityComponent<HierarchyComponent>(unmovedIndex);

        if(std::find(current.children.begin(), current.children.end(), entityID) == current.children.end()){
            current.children.push_back(entityID);
        }
        GetEntityComponent<HierarchyComponent>(entityID).parent = current.GetSparseIndex();
        Log::Print("ECS: Added child ", entityID, " to parent ", current.GetSparseIndex());
    };
    
    void HierarchyComponent::SetParent(u32 entityID) {
        ECS::Registry& reg = ECS::Registry::GetInstance();
        
        // Add hierarchy component to target entity if it has none
        if(!reg.GetComponentSparseSet<HierarchyComponent>().Contains(entityID)) {
            AddEntityComponent<HierarchyComponent>(entityID);
        }
        
        this->parent = entityID;
        HierarchyComponent& comp = GetEntityComponent<HierarchyComponent>(entityID);
        if(std::find(comp.children.begin(), comp.children.end(), this->GetSparseIndex()) != comp.children.end()) {
            comp.children.push_back(this->GetSparseIndex());
            Log::Print("ECS: Added parent ", entityID, " to child ", this->GetSparseIndex());
        }
    }
}