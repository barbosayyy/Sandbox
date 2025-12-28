#include "ScriptRegistry.h"

namespace Sb {
    namespace Scripting {
        std::unique_ptr<IScript> ScriptRegistry::CreateScript(const std::string& name) {
            auto it = _registry.find(name);
            if (it != _registry.end()) {
                return std::unique_ptr<IScript>(it->second());
            }
            return nullptr;
        }
    }
}