#include "ResourceManager.h"
#include "Core/Utils.h"
#include "Core/Debug.h"
#include "Resources.h"
#include <filesystem>

#include <string>

namespace Sb {

    namespace ResourceManagement {
        
        static void WriteResourceManifest() {
            if(!std::filesystem::exists(SB_RESOURCE_FOLDER_PATH))
                std::filesystem::create_directories(SB_RESOURCE_FOLDER_PATH);

            String buffer;

            if(!std::filesystem::exists(SB_RESOURCE_MANIFEST_PATH)) {
                for(const auto& dirEntry : std::filesystem::recursive_directory_iterator(SB_RESOURCE_FOLDER_PATH)) {
                    buffer = dirEntry.path().string().find_last_of("/\\.");
                }
            }
        }

        static void LoadResourceManifest() {
            SB_NOT_IMPL;
        }
    }

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
            Log::Warn("Resource Manager: Failed to find resource of matching ID.");
            return "";
        }
    }
    
    #include "yaml-cpp/yaml.h"
    
    Resource ResourceManager::GetDataFromID(ResourceID rId, int id)
    {
        String rName = GetYamlResourceNameFromResourceID(rId);
        Resource rData {0, "", ""};
        YAML::Node resourceNode = YamlUtil::GetNode(String(&SB_RESOURCES_PATH.c_str(), rName.c_str());
    
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

}


