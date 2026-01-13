#pragma once

#include <memory>
#include <string>

namespace Sb {
    namespace Scripting {
        class IScript;
        using ScriptCreator = IScript* (*)();
        extern "C" void RegisterScriptAPI(const char* name, Sb::Scripting::ScriptCreator creator);
    }
}

class IScript {
public:
    virtual ~IScript() = default;

    virtual void OnStart() {}
    virtual void OnUpdate(float deltaTime) {}
    virtual void OnDestroy() {}
};

#define REGISTER_SCRIPT(ClassName) \
    extern "C" { \
        __declspec(dllexport) IScript* Create##ClassName() { \
            return new ClassName(); \
        } \
        __declspec(dllexport) void Register##ClassName() { \
            Sb::Scripting::RegisterScriptAPI(#ClassName, reinterpret_cast<Sb::Scripting::ScriptCreator>(&Create##ClassName)); \
        } \
    }