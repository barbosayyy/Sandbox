#include "RenderSystem.h"
#include "ECS/Components.h"

namespace Sb {
    namespace ECS {
        void RenderSystem::Update(Registry& registry) {
            Renderer& ren = Renderer::GetInstance();
            
            for(MeshComponent meshComponent : registry.GetComponentStoreDense<MeshComponent>()) {
                if(registry.GetComponentSparseSet<TransformComponent>().Contains(meshComponent.sparseIndex)) {
                    meshComponent.model->Draw(&ren,
                         registry.GetComponent<TransformComponent>(meshComponent.sparseIndex).pos,
                          registry.GetComponent<TransformComponent>(meshComponent.sparseIndex).rot,
                           registry.GetComponent<TransformComponent>(meshComponent.sparseIndex).scale);
                }
            }
        }
    }
}
