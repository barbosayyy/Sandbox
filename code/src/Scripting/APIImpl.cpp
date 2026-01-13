#include "ScriptRegistry.h"

namespace Sb {
    namespace Scripting{
        extern "C" void RegisterScriptAPI(const char* name, Sb::Scripting::ScriptCreator creator) {
            ScriptRegistry::GetInstance().RegisterScript(name, creator);
        }
    }
}