#include "RenderSystem.h"
#include "ECS/Components.h"

namespace Sb {
    namespace ECS {
        void RenderSystem::Update(Registry& registry) {
            Renderer& ren = Renderer::GetInstance();
            
            for(MeshComponent meshComponent : registry.GetComponentStoreDense<MeshComponent>()) {
                if(registry.GetComponentSparseSet<TransformComponent>().Contains(meshComponent.sparseIndex)) {
                    vec3 pos = registry.GetComponent<TransformComponent>(meshComponent.sparseIndex).pos;
                    meshComponent.model->Draw(&ren, pos);
                }
            }
        }
    }
}
