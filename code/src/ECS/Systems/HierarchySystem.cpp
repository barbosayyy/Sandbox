#include "HierarchySystem.h"
#include "Core/Base.h"
#include "ECS/Components.h"

namespace Sb {
    namespace ECS {
        void HierarchySystem::Update(Registry& registry) {
            Renderer& ren = Renderer::GetInstance();
            
            for(HierarchyComponent hierarchyComponent : registry.GetComponentStoreDense<HierarchyComponent>()) {
                if(registry.GetComponentSparseSet<TransformComponent>().Contains(hierarchyComponent.GetSparseIndex())) {
                    for(Entity childEntity : hierarchyComponent.children) {
                        if(registry.GetComponentSparseSet<TransformComponent>().Contains(childEntity)) {
                            auto& childTransform = registry.GetComponent<TransformComponent>(childEntity) ;
                            auto& thisTransform = registry.GetComponent<TransformComponent>(hierarchyComponent.GetSparseIndex()) ;
                            
                            childTransform.scale = thisTransform.scale*childTransform.localScale;
                            childTransform.rotation = thisTransform.rotation*childTransform.localRotation;
                            childTransform.position = thisTransform.position*childTransform.localPosition;
                        }
                    }
                }
            }
        }
    }
}
