#pragma once

#include "Core/Singleton.h"
#include "IScript.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace Sb {
    namespace Scripting {
        class ScriptRegistry : public Singleton<ScriptRegistry, int>{
            std::unordered_map<std::string, ScriptCreator> _registry;
        public:
            void RegisterScript(const std::string& name, ScriptCreator creator);

            std::unique_ptr<IScript> CreateScript(const std::string& name);

            const auto& GetRegisteredScripts() const { return _registry; };
        };
    }
}