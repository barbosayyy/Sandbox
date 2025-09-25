#include "ResourceManager.h"
#include "Core/Utils.h"
#include "Core/Debug.h"
#include "Resources.h"
#include <filesystem>

#include <string>
#include <unordered_set>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/yaml.h"

namespace Sb {

    namespace ResourceManagement {
        
        static u32 assetUuid {0};
        
        void WriteAssetMetaData(String& buffer, std::filesystem::directory_entry dirEntry, YAML::Emitter& emitter);
        void WriteAssetMetaData(std::filesystem::directory_entry dirEntry, YAML::Node& node);
        bool FindNewAssetReference(std::filesystem::directory_entry dirEntry, std::unordered_set<std::string>& manifestPaths, std::unordered_set<std::string>& foundPaths, YAML::Node& node);

        void WriteAssetMetaData(String& buffer, std::filesystem::directory_entry dirEntry, YAML::Emitter& emitter) {
            emitter << YAML::BeginMap;
            emitter << YAML::Key << "id" << YAML::Value << assetUuid;
            buffer = dirEntry.path().string().substr(dirEntry.path().string().find_last_of("\\")+1);
            emitter << YAML::Key << "name" << YAML::Value << std::string(buffer);
            emitter << YAML::Key << "path" << YAML::Value << dirEntry.path().string();
            emitter << YAML::EndMap;
            assetUuid++;
        }

        void WriteAssetMetaData(std::filesystem::directory_entry dirEntry, YAML::Node& node) {
            YAML::Node entry;

            if(!node["assets"]) return;
            if(!node["assets"].IsSequence()) return;

            entry["id"] = assetUuid++;
            entry["name"] = dirEntry.path().filename().string();
            entry["path"] = dirEntry.path().string();

            node["assets"].push_back(entry);
        }

        // Reference new asset path by looking for another path with same file name and verify if that entry is not in the manifest already
        bool FindNewAssetReference(std::filesystem::directory_entry dirEntry, std::unordered_set<std::string>& manifestPaths, std::unordered_set<std::string>& foundPaths, YAML::Node& node) {
            for(auto entry : foundPaths) {
                std::filesystem::directory_entry entryDir(entry);
                
                if(dirEntry.path() != entryDir.path() && dirEntry.path().filename() == entryDir.path().filename()) {
                    if(!(manifestPaths.count(entryDir.path().string()) > 0)) {
                        node["path"] = entryDir.path().string();
                        
                        Log::Info("ResourceManifest: Fixed missing asset reference path ", dirEntry.path().string() , " to ", entryDir.path().string());
                        
                        return true;
                    }
                }
            }
            return false;
        }

        /* 
            Generate Assets metadata manifest
        */
        static void WriteResourceManifest() {
            if(!std::filesystem::exists(SB_RESOURCE_FOLDER_PATH))
                std::filesystem::create_directories(SB_RESOURCE_FOLDER_PATH);

            String buffer;

            YAML::Emitter emitter;

            // No resource manifest exists
            if(!std::filesystem::exists(SB_RESOURCE_MANIFEST_PATH)) {
                
                assetUuid = 0;
                
                emitter << YAML::BeginMap;
                emitter << YAML::Key << "assets";
                emitter << YAML::BeginSeq;
                
                for(const auto& dirEntry : std::filesystem::recursive_directory_iterator(SB_RESOURCE_FOLDER_PATH)) {
                    
                    if(!dirEntry.exists())
                    continue;
                    
                if(!std::filesystem::is_directory(dirEntry)) {
                        WriteAssetMetaData(buffer, dirEntry, emitter);
                    }
                }

                if(!File::Write(emitter.c_str(), SB_RESOURCE_FOLDER_PATH, "resource_manifest.yaml")) {
                    Log::Info("ResourceManifest: Failed to write resource manifest ", SB_RESOURCE_MANIFEST_PATH);
                    return;
                }
                Log::Info("ResourceManifest: Resource manifest written to ", SB_RESOURCE_MANIFEST_PATH);
            }

            // Load resource manifest and update its contents
            else {
                YAML::Node manifestRootNode = YAML::LoadFile(SB_RESOURCE_MANIFEST_PATH);
                std::unordered_set<std::string> resourceAssetPaths;
                std::unordered_set<std::string> manifest;
                u32 manifestID = 0;
                bool manifestIsDirty = false;
                
                if(manifestRootNode && manifestRootNode["assets"]) {
                    
                    // Register every asset directory entry in resources folder
                    for(const auto& dirEntry : std::filesystem::recursive_directory_iterator(SB_RESOURCE_FOLDER_PATH)) {
                        if(!dirEntry.exists())
                            continue;
                        if(!std::filesystem::is_directory(dirEntry) && dirEntry.path().string() != SB_RESOURCE_MANIFEST_PATH) {
                            resourceAssetPaths.insert(dirEntry.path().string());
                        }
                    }

                    // Get paths in manifest as set
                    for(auto node : manifestRootNode["assets"]) {
                        manifest.emplace(node["path"].as<std::string>(), node["id"].as<u32>());
                        if(node["id"].as<int>() > manifestID)
                            manifestID = node["id"].as<int>();
                    }
                
                    // Remove non-existing entries in manifest and add new ones; Fix mismatching references
                    for(size_t i = 0; i < manifestRootNode["assets"].size();) {
                        YAML::Node entry = manifestRootNode["assets"][i];
                        if(entry["id"] && entry["path"]) {
                            if(!(resourceAssetPaths.count(entry["path"].as<std::string>()) > 0)){
                                if(!FindNewAssetReference(std::filesystem::directory_entry(entry["path"].as<std::string>()), manifest, resourceAssetPaths, entry)) {
                                    manifestRootNode["assets"].remove(i);
                                    manifest.erase(entry["path"].as<std::string>());
                                    Log::Print(manifestRootNode["assets"]);
                                    Log::Info("ResourceManifest: Removed asset ", entry["path"].as<std::string>());
                                    continue;
                                }
                                manifestIsDirty = true;
                            }
                            ++i;
                        }
                    }

                    assetUuid = manifestID+1;

                    // Now update set with new entries
                    for(auto entry : resourceAssetPaths) {
                        if(!(manifest.count(entry) > 0)) {
                            Log::Info("ResourceManifest: Found new asset ", entry);
                            WriteAssetMetaData(std::filesystem::directory_entry(entry), manifestRootNode);
                            manifestIsDirty = true;
                        }
                    }

                    if(manifestIsDirty) {
                        
                        // Write modified node to a new manifest
                        emitter << manifestRootNode;

                        if(!File::Write(emitter.c_str(), SB_RESOURCE_FOLDER_PATH, "resource_manifest.yaml")) {
                            Log::Info("ResourceManifest: Failed to overwrite Resource manifest to ", SB_RESOURCE_MANIFEST_PATH);
                        }
                        Log::Info("ResourceManifest: Overwritten Resource manifest to ", SB_RESOURCE_MANIFEST_PATH);
                    }
                }
                else {
                    Log::Info("ResourceManifest: Invalid manifest");
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
    
    Resource ResourceManager::GetDataFromID(ResourceID rId, int id) {
        String rName = GetYamlResourceNameFromResourceID(rId);
        Resource rData {0, "", ""};
        YAML::Node resourceNode = YamlUtil::GetNode(SB_RESOURCE_MANIFEST_PATH.c_str(), rName.c_str());
        
        // Wrap this in YAML util function
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


