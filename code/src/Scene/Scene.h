#pragma once

#include "Core/Base.h"
#include "ECS/ComponentManager.h"

#include <unordered_map>
#include <bitset>

namespace SbEngine{
    class Scene{
    public:
        Scene();
        ~Scene();

        void AddEntity();
        void RemoveEntity(u32 entityID);

        void AddEntityComponent(u32 entityID, size_t componentMask);
        void RemoveEntityComponent(u32 entityID, size_t componentMask);
    private:
        std::unordered_map<u32, std::bitset<128>> _entities;
        ComponentManager _componentManager;
        u32 _nextEntityId;
    };
}
