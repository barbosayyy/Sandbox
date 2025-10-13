#include "GeometryPass.h"
#include "Core/Profiler.h"
#include "ECS/Registry.h"
#include "ECS/Systems/RenderSystem.h"
#include "Rendering/Renderer.h"

namespace Sb {
    void GeometryPass::Execute() {
        Profiler::StartRecord("Geometrypass");
        ECS::Registry& reg = ECS::Registry::GetInstance();
        Renderer& renderer = Renderer::GetInstance();
        
        ECS::RenderSystem::Update(reg);
        Profiler::StopRecord("Geometrypass");
    }
}