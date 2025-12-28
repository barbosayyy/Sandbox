#pragma once

namespace Sb {
    namespace Scripting {
        class IScript {
        public:
            virtual ~IScript() = default;

            virtual void OnStart();
            virtual void OnUpdate(float deltaTime);
            virtual void OnDestroy();
        };

        using ScriptCreator = IScript* (*)();
    }
}