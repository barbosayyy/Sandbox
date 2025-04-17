#include "Core/Base.h"
#include "ECS/Components.h"

#include "unordered_map"
#include "set"

namespace SbEngine{
    class ComponentManager {
    public:
        void AddComponent(u32 entityID, size_t componentID);
        void RemoveComponent(u32 entityID, size_t componentID);
        void RemoveAllComponents(u32 entity);
    private:
        
        // vector of Unordered map<size_t, Component(base)>
        // Keeps track of access to component data via the Component ID
        // as the first field

        std::unordered_map<size_t ,std::unordered_map<u32, Component>> _activeComponents;
        
        // <std::unordered_map<u32, Transform>> _transformComponents;
        
        //
        // std::vector<Transform> _transformComponents;
        // std::unordered_map<u16, size_t> _transformEntityIndex;
    };
}