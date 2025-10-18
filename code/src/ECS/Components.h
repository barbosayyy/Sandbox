#pragma once

#include "Rendering/Model.h"
#include "Rendering/Cubemap.h"
#include "Rendering/Light.h"

namespace Sb {

    // Component IDs
        constexpr size_t DUMMY_COMPONENT = 0;
        constexpr size_t TRANSFORM_COMPONENT = 1;
        constexpr size_t RENDERER_COMPONENT = 2;
}

namespace Sb {
    struct ComponentBase {
        u32 sparseIndex;
    };

    struct AssetComponentBase : ComponentBase{
        u32 assetID;
    };

    struct DummyComponent : ComponentBase {
    };

    struct TransformComponent : ComponentBase {
        vec3 pos {1.0f};

        vec3 rot {0.0f};
        
        vec3 scale {1.0f};
    };
    
    struct MeshComponent : AssetComponentBase {
        Model* model;
        // resource manifest uuid
    };

    struct SkyboxComponent : AssetComponentBase {
        Cubemap* cubemap;
    };

    struct LightComponent : ComponentBase {
        Light light;
    };
}
