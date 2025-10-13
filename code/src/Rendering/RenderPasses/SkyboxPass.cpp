#include "SkyboxPass.h"
#include "Core/Profiler.h"
#include "ECS/Registry.h"
#include "ECS/Systems/SkyboxSystem.h"

namespace Sb {

    void SkyboxPass::Execute() {
        Profiler::StartRecord("Skyboxpass");
        ECS::Registry& reg = ECS::Registry::GetInstance();
        
        ECS::SkyboxSystem::Update(reg);
        Profiler::StopRecord("Skyboxpass");
    }
}