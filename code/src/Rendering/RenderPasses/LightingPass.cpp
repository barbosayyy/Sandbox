#include "LightingPass.h"
#include "Core/Debug.h"
#include "Core/Profiler.h"
#include "Resources/ResourceManagement.h"

namespace Sb {

    LightingPass::LightingPass() {
        lightingPassShader = ResourceManagement::LoadShader(41, 40);

        numLights = 32;

		srand(13);
		for (unsigned int i = 0; i < numLights; i++)
		{
			// calculate slightly random offsets
			float xPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			float yPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 4.0);
			float zPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			lightPos.push_back(glm::vec3(xPos, yPos, zPos));
			// also calculate random color
			float rColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5);
			float gColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5);
			float bColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5);
			lightCol.push_back(glm::vec3(rColor, gColor, bColor));
		}
    }

    void LightingPass::Execute() {
        Profiler::StartRecord("Lightpass");
        if(lightingPassShader == nullptr)
            Shader* lightingPassShader = ResourceManagement::LoadShader(41, 40);
        
        if(init == false) {
            lightingPassShader->Use();
            lightingPassShader->SetInt("gPosition", 0);
            lightingPassShader->SetInt("gNormal", 1);
            lightingPassShader->SetInt("gAlbedoSpec", 2);
		    lightingPassShader->SetVec3("ambient", vec3(0.1f));
            for(unsigned int i = 0; i < lightPos.size(); i++){
                lightingPassShader->SetVec3(String("lights[" + std::to_string(i) + "].position").c_str(), lightPos[i]);
                lightingPassShader->SetVec3(String("lights[" + std::to_string(i) + "].color").c_str(), lightCol[i]);
                const float constant = 1.0f;
                const float linear = 0.7f;
                const float quadratic = 1.8f;
                lightingPassShader->SetFloat(String("lights[" + std::to_string(i) + "].linear").c_str(), linear);
                lightingPassShader->SetFloat(String("lights[" + std::to_string(i) + "].quadratic").c_str(), quadratic);
                const float maxBrightness = std::fmaxf(std::fmaxf(lightCol[i].r, lightCol[i].g), lightCol[i].b);
                float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f/5.0f) * maxBrightness))) / (2.0f * quadratic);
                lightingPassShader->SetFloat(String("lights[" + std::to_string(i) + "].radius").c_str(), radius);
            }
            Log::Print("Lighting pass init");
            init = true;
        }

        Renderer& renderer = Renderer::GetInstance();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        lightingPassShader->Use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, renderer.gPosition);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, renderer.gNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, renderer.gAlbedoSpec);
        
        lightingPassShader->SetVec3("viewPos", renderer.GetRenderCamera()->_position);

        renderer.DrawFramebufferQuad(false);

        // Copy geometry depth to default framebuffer
        glBindFramebuffer(GL_READ_FRAMEBUFFER, renderer._gBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(0, 0, renderer.GetViewportWidth(), renderer.GetViewportHeight(), 0, 0, renderer.GetViewportWidth(), renderer.GetViewportHeight(), GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        Profiler::StopRecord("Lightpass");
    }
}