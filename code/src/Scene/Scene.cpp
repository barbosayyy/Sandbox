#include "Scene/Scene.h"

#include <cstddef>

using namespace Sb;
Scene::Scene() : _nextEntityId(0){}

Scene::~Scene(){}

u32 Scene::AddEntity(){
    _componentManager.AddComponent<DummyComponent>(_nextEntityId);
    return _nextEntityId++;
}

void Scene::RemoveEntity(u32 entityID){
    _componentManager.RemoveAllComponents(entityID);
}