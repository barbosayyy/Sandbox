#include "ECS/ComponentManager.h"
#include "Components.h"
#include <cstddef>
#include <iterator>
#include <unordered_map>

using namespace SbEngine;

    void ComponentManager::AddComponent(u32 entityID, size_t componentID){
        auto it = _activeComponents.find(componentID);
        if(it != _activeComponents.end()){
            std::unordered_map<u32, Component> componentMap;
            componentMap.insert(std::make_pair(entityID, GetComponentFromID(componentID)));
            _activeComponents.insert(std::make_pair(componentID, componentMap));
        }
    }
    
    void ComponentManager::RemoveComponent(u32 entityID, size_t componentID){
        auto it = _activeComponents[componentID].find(entityID);
        if(it != _activeComponents[componentID].end()){
            _activeComponents[componentID].erase(entityID);
        }
    }