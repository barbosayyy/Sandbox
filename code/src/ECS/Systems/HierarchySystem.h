#pragma once

#include "ECS/Registry.h"

namespace Sb {
    namespace ECS {
        class HierarchySystem {
        public:
            static void Update(Registry& registry);
        };
    }
}