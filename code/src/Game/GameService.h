#pragma once

#include "Core/Types.h"

namespace Sb {
    class GameService {
    public:
        void LoadGameLibrary(const String& path);

        void AttachScript(Entity entityID, std::string scriptName);
    };
}