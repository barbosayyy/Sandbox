#include "LightingPass.h"
#include "Core/Debug.h"
#include "Core/Profiler.h"
#include "ECS/Registry.h"
#include "Resources/ResourceManagement.h"
#include "Rendering/OpenGL/GLBuffer.h"
#include "ECS/Systems/LightSystem.h"

namespace Sb {

    LightingPass::LightingPass() {
        lightingPassShader = ResourceManagement::LoadShader("common/shaders/LightingPass.vert", "common/shaders/LightingPassUBO.frag");
    }

    void LightingPass::Execute() {
        Profiler::StartRecord("Lightpass");
        ECS::Registry& reg = ECS::Registry::GetInstance();
        Renderer& renderer = Renderer::GetInstance();

        if(lightingPassShader != nullptr) {

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            lightingPassShader->Use();
            
            if(renderer._stateShowBufferMask == 0) {
                lightingPassShader->SetInt("gPosition", 0);
                lightingPassShader->SetInt("gNormal", 1);
                lightingPassShader->SetInt("gAlbedoSpec", 2);
            } else if(renderer._stateShowBufferMask == 1){
                lightingPassShader->SetInt("gPosition", 0);
                lightingPassShader->SetInt("gNormal", 0);
                lightingPassShader->SetInt("gAlbedoSpec", 0);
            } else if(renderer._stateShowBufferMask == 2){
                lightingPassShader->SetInt("gPosition", 1);
                lightingPassShader->SetInt("gNormal", 1);
                lightingPassShader->SetInt("gAlbedoSpec", 1);
            } else if(renderer._stateShowBufferMask == 3){
                lightingPassShader->SetInt("gPosition", 2);
                lightingPassShader->SetInt("gNormal", 2);
                lightingPassShader->SetInt("gAlbedoSpec", 2);
            }

            // First frame lighting UBO upload
            if(init == false) {

                lightingPassShader->SetVec3("ambientLight", vec3(0.3f));

                ECS::LightSystem::Update(reg);

                GLBufferLightUBO(renderer._glLightData.lightUBO, renderer._glLightData.lightUBOData);
                init = true;
            }
            
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
        }
        Profiler::StopRecord("Lightpass");
    }
}