#include "RenderSystem.h"
#include "ECS/Components.h"

namespace Sb {
    namespace ECS {
        void RenderSystem::Update(Registry& registry) {
            Renderer& ren = Renderer::GetInstance();
            
            for(MeshComponent meshComponent : registry.GetComponentStoreDense<MeshComponent>()) {
                if(registry.GetComponentSparseSet<TransformComponent>().Contains(meshComponent.GetSparseIndex())) {
                    
                    // Updated transform used on draw
                    if(meshComponent.model != nullptr)
                        meshComponent.model->Draw(&ren,
                            registry.GetComponent<TransformComponent>(meshComponent.GetSparseIndex()).position,
                            registry.GetComponent<TransformComponent>(meshComponent.GetSparseIndex()).rotation,
                            registry.GetComponent<TransformComponent>(meshComponent.GetSparseIndex()).scale);
                }
            }
        }
    }
}
