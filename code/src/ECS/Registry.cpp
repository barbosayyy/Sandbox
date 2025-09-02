#include "Registry.h"

#include "ECS/Systems/RenderSystem.h"

namespace Sb {
    namespace ECS {
        Registry::Registry() : _nextEntityId(0) {}
        Registry::~Registry() {}
    }
}