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
        vec3 localPosition {0.0f};
        vec3 localRotation {0.0f};
        vec3 localScale {1.0f};
        vec3 position {0.0f};
        vec3 rotation {0.0f};
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

    struct HierarchyComponent : ComponentBase {
        Entity parent;
        std::vector<Entity> children;

        void AddChild(u32 entityID);
        void SetParent(u32 entityID);
    };
}
