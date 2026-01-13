#pragma once

#include "Core/Base.h"
#include "Rendering/Model.h"
#include "Rendering/Cubemap.h"
#include "Rendering/Light.h"
#include "Core/Collections.h"
#include "Scripting/IScript.h"

namespace Sb {

    // Component IDs
        constexpr size_t DUMMY_COMPONENT = 0;
        constexpr size_t TRANSFORM_COMPONENT = 1;
        constexpr size_t RENDERER_COMPONENT = 2;
}

namespace Sb {
    struct ComponentBase {
        // Returns underlying sparse index of entity in component storage
        u32 GetSparseIndex() const { return sparseIndex; }
    private:
        u32 sparseIndex;

        template<typename T>
        friend struct SparseSet;
    };
    
    struct AssetComponentBase : ComponentBase{
        // Returns asset index
        u32 GetAssetID() const { return assetID; }
    private:
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
        Entity parent {_MAX_U32};
        std::vector<Entity> children;

        void AddChild(u32 entityID);
        void SetParent(u32 entityID);
    };

    struct ScriptComponent : ComponentBase {
        ScriptComponent& operator=(const ScriptComponent&) = delete;  
        std::unique_ptr<Scripting::IScript> script;
        ScriptComponent(ScriptComponent&&) noexcept = default;
        ScriptComponent& operator=(ScriptComponent&&) noexcept = default;
    };
}
