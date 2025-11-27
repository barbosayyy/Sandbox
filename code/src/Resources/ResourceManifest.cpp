#include "ResourceManifest.h"

#include "Core/Crypto.h"
#include "Core/Types.h"
#include "Core/Utils.h"
#include "Core/Config.h"
#include "Core/Debug.h"

#include <filesystem>
#include <unordered_set>
#include "yaml-cpp/emitter.h"
#include "yaml-cpp/yaml.h"

namespace Sb {
    namespace ResourceManagement {

        // --- Private

#ifdef SB_BUILD_DEBUG
        // #define SB_BUILD_DEBUG_RESOURCE_MANIFEST
#endif
        
        void WriteAssetMetaData(std::filesystem::directory_entry dirEntry, YAML::Emitter& emitter, const SbGUID& assetGUID);
        void WriteAssetMetaData(std::filesystem::directory_entry dirEntry, YAML::Node& node, const SbGUID& assetGUID);
        bool FindNewAssetReference(std::filesystem::directory_entry dirEntry, std::unordered_set<std::string>& manifestPaths, std::unordered_set<std::string>& foundPaths, YAML::Node& node);

        // Write utils
            void WriteAssetMetaData(std::filesystem::directory_entry dirEntry, YAML::Emitter& emitter, const SbGUID& assetGUID) {
                emitter << YAML::BeginMap;
                emitter << YAML::Key << "id" << YAML::Value << std::string(Crypto::GetStringFromGUID(assetGUID));
                emitter << YAML::Key << "name" << YAML::Value << dirEntry.path().filename().string();
                emitter << YAML::Key << "path" << YAML::Value << File::ToUnixPathStyle(dirEntry.path().string());
                emitter << YAML::EndMap;
            }

            void WriteAssetMetaData(std::filesystem::directory_entry dirEntry, YAML::Node& node, const SbGUID& assetGUID) {
                YAML::Node entry;

                if(!node["assets"]) return;
                if(!node["assets"].IsSequence()) return;

                entry["id"] = std::string(Crypto::GetStringFromGUID(assetGUID));
                entry["name"] = dirEntry.path().filename().string();
                entry["path"] = File::ToUnixPathStyle(dirEntry.path().string());

                node["assets"].push_back(entry);
            }

        // Find reference to new asset path in node
        bool FindNewAssetReference(std::filesystem::directory_entry dirEntry, std::unordered_set<std::string>& manifestPaths, std::unordered_set<std::string>& foundPaths, YAML::Node& node) {
            for(auto entry : foundPaths) {
                std::filesystem::directory_entry entryDir(entry);
                
                // Look for another path with same file name
                if(dirEntry.path() != entryDir.path() && dirEntry.path().filename() == entryDir.path().filename()) {
                    
                    // Verify that the entry is not in the manifest already - Update node
                    if(!(manifestPaths.count(entryDir.path().string()) > 0)) {
                        node["path"] = File::ToUnixPathStyle(entryDir.path().string());
                        
                        Log::Info("ResourceManifest: Fixed missing asset reference path ", File::ToUnixPathStyle(dirEntry.path().string()) , " to ", node["path"]);
                        
                        return true;
                    }
                }
            }
            return false;
        }

        // --- Public

        // Generate Asset manifest
        bool WriteResourceManifest() {

            if(!std::filesystem::exists(SB_RESOURCE_FOLDER_PATH))
                std::filesystem::create_directories(SB_RESOURCE_FOLDER_PATH);

            YAML::Emitter emitter;

            // No resource manifest exists
            if(!std::filesystem::exists(SB_RESOURCE_MANIFEST_PATH)) {
                
                emitter << YAML::BeginMap;
                emitter << YAML::Key << "assets";
                emitter << YAML::BeginSeq;
                
                for(const auto& dirEntry : std::filesystem::recursive_directory_iterator(SB_RESOURCE_FOLDER_PATH)) {
                    
                    if(!dirEntry.exists())
                        continue;

                    // Skip common assets
                    if((dirEntry.path().string().rfind("resources/common", 0) == 0 || dirEntry.path().string().rfind("resources\\common", 0) == 0) )
                        continue;
                    
                    if(!std::filesystem::is_directory(dirEntry)) {
                        const SbGUID guid = Crypto::NewGUID();
                        WriteAssetMetaData(dirEntry, emitter, guid);
                    }
                }

                if(!File::Write(emitter.c_str(), SB_RESOURCE_FOLDER_PATH, "resource_manifest.yaml")) {
                    Log::Info("ResourceManifest: Failed to write resource manifest ", SB_RESOURCE_MANIFEST_PATH);
                    return false;
                }
                Log::Info("ResourceManifest: New Resource Manifest written to ", SB_RESOURCE_MANIFEST_PATH);
                return true;
            }

            // Load existing resource manifest and update its contents
            else {
                YAML::Node manifestRootNode = YAML::LoadFile(SB_RESOURCE_MANIFEST_PATH);

                if(manifestRootNode["assets"].size() <= 0) {
                    std::filesystem::remove(SB_RESOURCE_MANIFEST_PATH);
                    return WriteResourceManifest();
                }

                std::unordered_set<std::string> resourceAssetPaths;
                std::unordered_set<std::string> manifest;
                u32 manifestID = 0;
                bool manifestIsDirty = false;
                
                if(manifestRootNode && manifestRootNode["assets"]) {
                    
                    for(const auto& dirEntry : std::filesystem::recursive_directory_iterator(SB_RESOURCE_FOLDER_PATH)) {
                        if(!dirEntry.exists())
                            continue;
                        if((dirEntry.path().string().rfind("resources/common", 0) == 0 || dirEntry.path().string().rfind("resources\\common", 0) == 0) )
                            continue;
                        
                        // Get paths in resources directory as set
                        if(!std::filesystem::is_directory(dirEntry) && File::ToUnixPathStyle(dirEntry.path().string()) != SB_RESOURCE_MANIFEST_PATH) {
                            resourceAssetPaths.insert(File::ToUnixPathStyle(dirEntry.path().string()));
                        }
                    }

                    // Add existing manifest paths to NEW manifest set to rewrite
                    for(auto node : manifestRootNode["assets"]) {
                        manifest.emplace(node["path"].as<std::string>());
                    }
                
                    // Remove non-existing entries in manifest; Fix mismatching references
                    for(size_t i = 0; i < manifestRootNode["assets"].size();) {
                        YAML::Node entry = manifestRootNode["assets"][i];
                        if(entry["id"] && entry["path"]) {
                            if(!(resourceAssetPaths.count(entry["path"].as<std::string>()) > 0)){
                                if(!FindNewAssetReference(std::filesystem::directory_entry(entry["path"].as<std::string>()), manifest, resourceAssetPaths, entry)) {
                                    manifestRootNode["assets"].remove(i);
                                    manifest.erase(entry["path"].as<std::string>());
#ifdef SB_BUILD_DEBUG_RESOURCE_MANIFEST
                                    Log::Print(manifestRootNode["assets"]);
#endif
                                    Log::Info("ResourceManifest: Removed asset ", entry["path"].as<std::string>());
                                    continue;
                                }
                                manifestIsDirty = true;
                            }
                            ++i;
                        }
                    }

                    // Now update set with new entries
                    for(auto entry : resourceAssetPaths) {
                        if(!(manifest.count(entry) > 0)) {
                            Log::Info("ResourceManifest: Found new asset ", entry);
                                const SbGUID guid = Crypto::NewGUID();
                                WriteAssetMetaData(std::filesystem::directory_entry(entry), manifestRootNode, guid);
                                manifestIsDirty = true;
                        }
                    }

                    if(manifestIsDirty) {
                        
                        // Write modified node to a new manifest
                        emitter << manifestRootNode;

                        if(!File::Write(emitter.c_str(), SB_RESOURCE_FOLDER_PATH, "resource_manifest.yaml")) {
                            Log::Info("ResourceManifest: Failed to overwrite Resource manifest to ", SB_RESOURCE_MANIFEST_PATH);
                            return false;
                        }
                        Log::Info("ResourceManifest: Overwritten Resource manifest to ", SB_RESOURCE_MANIFEST_PATH);
                        return true;
                    }
                }
                else {
                    Log::Info("ResourceManifest: Invalid manifest");
                    return false;
                }
            }
            return false;
        }
    }
}

