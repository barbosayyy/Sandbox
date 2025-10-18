#include "LightingPass.h"
#include "Core/Debug.h"
#include "Core/Profiler.h"
#include "ECS/Registry.h"
#include "Resources/ResourceManagement.h"
#include "Rendering/OpenGL/GLBuffer.h"
#include "ECS/Systems/LightSystem.h"

namespace Sb {

    LightingPass::LightingPass() {
        lightingPassShader = ResourceManagement::LoadShader(41, 53);
    }

    void LightingPass::Execute() {
        Profiler::StartRecord("Lightpass");
        if(lightingPassShader == nullptr)
            Shader* lightingPassShader = ResourceManagement::LoadShader(41, 53);
    
        ECS::Registry& reg = ECS::Registry::GetInstance();
        Renderer& renderer = Renderer::GetInstance();
        if(init == false) {
            lightingPassShader->Use();
            lightingPassShader->SetInt("gPosition", 0);
            lightingPassShader->SetInt("gNormal", 1);
            lightingPassShader->SetInt("gAlbedoSpec", 2);
		    lightingPassShader->SetVec3("ambientLight", vec3(0.1f));

            ECS::LightSystem::Update(reg);

            GLBufferLightUBO(renderer._lightUBO, renderer._lightUBOData);
            
            Log::Print("Lighting pass init");
            init = true;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        lightingPassShader->Use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, renderer.gPosition);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, renderer.gNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, renderer.gAlbedoSpec);
        
        lightingPassShader->SetVec3("viewPosition", renderer.GetRenderCamera()->_position);

        renderer.DrawFramebufferQuad(false);

        // Copy geometry depth to default framebuffer
        glBindFramebuffer(GL_READ_FRAMEBUFFER, renderer._gBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(0, 0, renderer.GetViewportWidth(), renderer.GetViewportHeight(), 0, 0, renderer.GetViewportWidth(), renderer.GetViewportHeight(), GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        Profiler::StopRecord("Lightpass");
    }
}