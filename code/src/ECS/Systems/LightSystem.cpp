#include "LightSystem.h"
#include "Core/Config.h"
#include "ECS/Components.h"

namespace Sb {
    namespace ECS {
        void LightSystem::Update(Registry &registry) {
            Renderer& ren = Renderer::GetInstance();
            u8 it = 0;
            const float constant = 1.0f; 
            for(LightComponent lightComponent : registry.GetComponentStoreDense<LightComponent>()) {
                if(registry.GetComponentSparseSet<TransformComponent>().Contains(lightComponent.sparseIndex)) {
                    if(it >= SB_RENDERER_MAX_NUM_LIGHTS) 
                        break;
                    ren._lightUBOData.lights[it].color = lightComponent.light.color;
                    ren._lightUBOData.lights[it].intensity = lightComponent.light.intensity;
                    ren._lightUBOData.lights[it].radius = lightComponent.light.range;
                    ren._lightUBOData.lights[it].type = (int)lightComponent.light.type;
                    ren._lightUBOData.lights[it].position = registry.GetComponent<TransformComponent>(lightComponent.sparseIndex).position;
                    ren._lightUBOData.lights[it].linear = 0.7f;
                    ren._lightUBOData.lights[it].quadratic = 1.8f;
                    const float maxBrightness = std::fmaxf(std::fmaxf(lightComponent.light.color.r, lightComponent.light.color.g), lightComponent.light.color.b);
                    float tempRadius = (-0.7f + std::sqrt(0.7f * 0.7f - 4 * 1.8f * (constant - (256.0f/5.0f) * maxBrightness))) / (2.0f * 1.8f);
                    ren._lightUBOData.lights[it].radius = tempRadius;
                }
                it++;
            }
            ren._lightUBOData.numLights = it;
        }
    }
}