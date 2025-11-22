#include "SkyboxSystem.h"
#include "ECS/Components.h"

namespace Sb {
    namespace ECS {
        void SkyboxSystem::Update(Registry& registry) {
            Renderer& ren = Renderer::GetInstance();
            
            for(SkyboxComponent skyboxComponent : registry.GetComponentStoreDense<SkyboxComponent>()) {
                if(skyboxComponent.cubemap != nullptr)
                    skyboxComponent.cubemap->Draw();
            }
        }
    }
}
