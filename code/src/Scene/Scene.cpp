#include "Scene/Scene.h"
#include "Core/Debug.h"

#include <cstddef>

using namespace SbEngine;
Scene::Scene() : _nextEntityId(0){}

Scene::~Scene(){}

void Scene::AddEntity(){
    _entities.insert(std::make_pair(_nextEntityId, std::bitset<128>()));
    AddEntityComponent(_nextEntityId, DUMMY_COMPONENT);
    _nextEntityId++;
}

void Scene::RemoveEntity(u32 entityID){
    _componentManager.RemoveAllComponents(entityID);
    _entities[entityID].reset();
}

void Scene::AddEntityComponent(u32 entityID, size_t componentMask){
    auto it = _entities.find(entityID);
    if(it != _entities.end()){
        _entities[entityID].set(componentMask);
        if(componentMask != DUMMY_COMPONENT){
            _componentManager.AddComponent(entityID, componentMask);
        }
    }
    else{
        Logger::Warn("ECS: Entity which you are trying to add a component to does not exist.");
    }
}
void Scene::RemoveEntityComponent(u32 entityID, size_t componentMask){
    auto it = _entities.find(entityID);
    if(it != _entities.end()){
        _entities[entityID].reset(componentMask);
        _componentManager.RemoveComponent(entityID, componentMask);
    }
}
