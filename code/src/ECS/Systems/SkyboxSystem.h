#pragma once

#include "ECS/Registry.h"

namespace Sb {
    namespace ECS {
        class SkyboxSystem {
        public:
            static void Update(Registry& registry);
        };
    }
}