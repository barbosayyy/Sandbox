#include "GLLightData.h"
#include "Rendering/Light.h"

namespace Sb {
    u32 GLLightData::lightUBO;
    LightUBOData GLLightData::lightUBOData = LightUBOData{};
}