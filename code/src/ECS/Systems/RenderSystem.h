#pragma once

#include "Core/Collections.h"
#include "ECS/Components.h"
#include "ECS/Registry.h"

namespace Sb {
    namespace ECS {
        class RenderSystem {
        public:
            static void Update(Registry& registry);
        };
    }
}