#include "ShaderManager.h"
#include "Core/Debug.h"

using namespace SbEngine;

// TODO: Load with Yaml loader

ShaderManager::ShaderManager() : _shaderCount(0), _defaultShader(nullptr){
}

void ShaderManager::Init(){
    ResourceManager::Init();
    _defaultShader = new Shader("resources/shaders/default.vert","resources/shaders/default.frag");
    _shaders.push_back(_defaultShader);
    _shaderData.emplace_back(-1, -1);
    _shaderCount++;
}
 
ShaderManager::~ShaderManager()
{
    for(Shader* shader : _shaders)
    {
        if(shader != nullptr){
            delete shader;
        }
    }
}

Shader* ShaderManager::GetShader(int vRId, int fRId)
{
    Shader* pSh;
    for(int i = 0; i < _shaderData.size(); i++){
        if(_shaderData.at(i).vertexID == vRId && _shaderData.at(i).fragmentID == fRId){
            pSh = _shaders.at(i);
            return pSh;
        }
    }

    pSh = NewShader(vRId, fRId);

    if(pSh == nullptr){
        pSh = _shaders.at(0);
        Logger::Warn("Shader Manager: Assigned default shader");
    }

    return pSh;
}

Shader* ShaderManager::NewShader(int vRId, int fRId)
{
    Logger::Print("Creating new Shader...");
    Resource vSh = GetDataFromID(ResourceID::SHADER_VERTEX, vRId);
    Resource fSh = GetDataFromID(ResourceID::SHADER_FRAGMENT, fRId);

    Shader* newSh = new Shader(vSh.path.c_str(), fSh.path.c_str());
    if(newSh->_shader == -1){
        return nullptr;
    }
    else{
        this->_shaders.push_back(newSh);
        this->_shaderData.emplace_back(vSh.id, fSh.id);
        _shaderCount++;
        return newSh;
    }
    
	//this->_shaders.emplace_back(new Shader(vertPath, fragPath));
	//this->_shaders.at(_shaderCount)->ShaderInstanceId() = _shaderNextId;
	//_shaderNextId++;
	//_shaderCount++;
}

void ShaderManager::RemoveShader(int pos)
{
	//if(pos >= 0 || pos <= _shaders.size()-1){
	//	std::vector<Shader*>::iterator it = _shaders.begin();
	//	std::advance(it, pos);
	//	_shaders.erase(it);
	//	_shaderCount--;
	//}
}