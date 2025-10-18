#include "Registry.h"

namespace Sb {
    namespace ECS {
        Registry::Registry() : _nextEntityId(0) {}
        Registry::~Registry() {}
    }
}