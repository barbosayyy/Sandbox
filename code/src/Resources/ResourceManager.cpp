#include "ResourceManager.h"
#include "Core/Utils.h"
#include "Core/Debug.h"
#include "Resources.h"

using namespace SbEngine;

ResourceManager::ResourceManager() : _init(false){

}

String ResourceManager::GetYamlResourceNameFromResourceID(ResourceID rId)
{
    switch(rId){
        case ResourceID::SHADER_FRAGMENT:
            return "fragment";
        break;
        case ResourceID::SHADER_VERTEX:
            return "vertex";
        break;
        
        case ResourceID::TEXTURE_JPG:
            return "jpg";
        break;
        case ResourceID::TEXTURE_PNG:
            return "png";
        break;
        Logger::Warn("Resource Manager: Failed to find resource of matching ID.");
        return "";
    }
}

#include "yaml-cpp/yaml.h"

Resource ResourceManager::GetDataFromID(ResourceID rId, int id)
{
    String rName = GetYamlResourceNameFromResourceID(rId);
    Resource rData {0, "", ""};
    YAML::Node resourceNode = YamlUtil::GetNode(SB_RESOURCE_DATA_PATH.c_str(), rName.c_str());

    // Wrap this in yaml util function
    int entryId {0};
    auto entries = resourceNode;
	if(entries){
		for(auto entry : entries){
			entryId = entry["id"].as<int>();
			if(entryId == id){
				rData.id = entryId;
                rData.name = entry["name"].as<std::string>();
                rData.path = entry["path"].as<std::string>();
			}
		}
	}

    return rData;
}