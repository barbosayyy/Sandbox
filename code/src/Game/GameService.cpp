#include "GameService.h"
#include "ECS/Components.h"
#include "ECS/Registry.h"
#include "Scripting/ScriptRegistry.h"

#ifdef SB_PLATFORM_WIN
#include <windows.h>
#endif

namespace Sb {
    void GameService::LoadGameLibrary(const String& path) {
#ifdef SB_PLATFORM_WIN
        HMODULE gameLib = LoadLibraryA(path.c_str());
        
        if(gameLib) {
            auto registerFunc = (void(*)())GetProcAddress(gameLib, "RegisterAllScripts");
            if(registerFunc) {
                registerFunc();
            }
        }
#endif
    }

    void GameService::AttachScript(Entity entityID, std::string scriptName) {
        ECS::Registry& reg = ECS::Registry::GetInstance();
        auto script = Scripting::ScriptRegistry::GetInstance().CreateScript(scriptName);
        if(script && reg.GetComponentSparseSet<DummyComponent>().Contains(entityID)) {
            reg.AddComponent<ScriptComponent>(entityID);
            reg.GetComponent<ScriptComponent>(entityID).script = std::move(script);
        }
    }
}