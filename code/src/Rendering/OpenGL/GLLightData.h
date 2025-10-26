#pragma once

#include "Core/Base.h"
#include "Rendering/Light.h"

namespace Sb {
    
    struct GLLightData {
        static u32 lightUBO;
        static LightUBOData lightUBOData;
    };
}