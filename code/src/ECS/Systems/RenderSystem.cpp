#include "RenderSystem.h"
#include "ECS/Components.h"

namespace Sb {
    namespace ECS {
        void RenderSystem::Update(Registry& registry) {
            Renderer& ren = Renderer::GetInstance();
            
            for(MeshComponent meshComponent : registry.GetComponentStoreDense<MeshComponent>()) {
                if(registry.GetComponentSparseSet<TransformComponent>().Contains(meshComponent.sparseIndex)) {
                    
                    // Updated transform used on draw
                    meshComponent.model->Draw(&ren,
                        registry.GetComponent<TransformComponent>(meshComponent.sparseIndex).position,
                        registry.GetComponent<TransformComponent>(meshComponent.sparseIndex).rotation,
                        registry.GetComponent<TransformComponent>(meshComponent.sparseIndex).scale);
                }
            }
        }
    }
}
