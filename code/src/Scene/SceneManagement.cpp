#include "Core/Base.h"
#include "ECS/Components.h"
#include "ECS/Registry.h"
#include "SceneManagement.h"

#include "Resources/ResourceManager.h"
#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"
#include <filesystem>

namespace Sb {
    namespace SceneManagement {
        
        template <typename T>
        void WriteSparseSetComponentData(SparseSet<T>& sparseSet, u32 entityID, YAML::Emitter& emitter) {
            if(sparseSet.Contains(entityID)) {
                ResourceManagement::ResourceManager& res = ResourceManagement::ResourceManager::GetInstance();
                vec3 temp;

                // Write component data
                if constexpr (std::is_same_v<T, TransformComponent>) {
                    emitter << YAML::Key << "Transform" << YAML::Value;
                    emitter << YAML::BeginMap;

                    emitter << YAML::Key << "position" << YAML::Value;
                    emitter << YAML::Flow << YAML::BeginMap;
                    temp = sparseSet.GetDense()[sparseSet.GetSparse()[entityID]].position;
                    emitter << YAML::Key << "x" << YAML::Value << temp.x;
                    emitter << YAML::Key << "y" << YAML::Value << temp.y;
                    emitter << YAML::Key << "z" << YAML::Value << temp.z;
                    emitter << YAML::EndMap;
                    
                    emitter << YAML::Key << "rotation" << YAML::Value;
                    emitter << YAML::Flow << YAML::BeginMap;
                    temp = sparseSet.GetDense()[sparseSet.GetSparse()[entityID]].rotation;
                    emitter << YAML::Key << "x" << YAML::Value << temp.x;
                    emitter << YAML::Key << "y" << YAML::Value << temp.y;
                    emitter << YAML::Key << "z" << YAML::Value << temp.z;
                    emitter << YAML::EndMap;

                    emitter << YAML::Key << "scale" << YAML::Value;
                    emitter << YAML::Flow << YAML::BeginMap;
                    temp = sparseSet.GetDense()[sparseSet.GetSparse()[entityID]].scale;
                    emitter << YAML::Key << "x" << YAML::Value << temp.x;
                    emitter << YAML::Key << "y" << YAML::Value << temp.y;
                    emitter << YAML::Key << "z" << YAML::Value << temp.z;
                    emitter << YAML::EndMap;

                    emitter << YAML::EndMap;
                }
                else if constexpr (std::is_same_v<T, MeshComponent>) {
                    emitter << YAML::Key << "Mesh" << YAML::Value;
                    emitter << YAML::BeginMap;
                    Log::Print(entityID);
                    Log::Print(sparseSet.GetDense()[sparseSet.GetSparse()[entityID]].model->_assetID);
                    emitter << YAML::Key << "id" << YAML::Value << std::string(Crypto::GetStringFromGUID(res.GetSbGUIDFromU32Hash(sparseSet.GetDense()[sparseSet.GetSparse()[entityID]].model->_assetID)));
                    
                    emitter << YAML::EndMap;
                }

                else if constexpr (std::is_same_v<T, SkyboxComponent>) {
                    emitter << YAML::Key << "Skybox" << YAML::Value;
                    emitter << YAML::BeginMap;
                    Log::Print(Crypto::GetStringFromGUID(res.GetSbGUIDFromU32Hash(sparseSet.GetDense()[sparseSet.GetSparse()[entityID]].cubemap->_textureFaceRightManifestID)));
                    emitter << YAML::Key << "textureFaceRightID" << YAML::Value << std::string(Crypto::GetStringFromGUID(res.GetSbGUIDFromU32Hash(sparseSet.GetDense()[sparseSet.GetSparse()[entityID]].cubemap->_textureFaceRightManifestID)));
                    emitter << YAML::Key << "textureFaceLeftID" << YAML::Value << std::string(Crypto::GetStringFromGUID(res.GetSbGUIDFromU32Hash(sparseSet.GetDense()[sparseSet.GetSparse()[entityID]].cubemap->_textureFaceLeftManifestID)));
                    emitter << YAML::Key << "textureFaceTopID" << YAML::Value << std::string(Crypto::GetStringFromGUID(res.GetSbGUIDFromU32Hash(sparseSet.GetDense()[sparseSet.GetSparse()[entityID]].cubemap->_textureFaceTopManifestID)));
                    emitter << YAML::Key << "textureFaceBottomID" << YAML::Value << std::string(Crypto::GetStringFromGUID(res.GetSbGUIDFromU32Hash(sparseSet.GetDense()[sparseSet.GetSparse()[entityID]].cubemap->_textureFaceBottomManifestID)));
                    emitter << YAML::Key << "textureFaceFrontID" << YAML::Value << std::string(Crypto::GetStringFromGUID(res.GetSbGUIDFromU32Hash(sparseSet.GetDense()[sparseSet.GetSparse()[entityID]].cubemap->_textureFaceFrontManifestID)));
                    emitter << YAML::Key << "textureFaceBackID" << YAML::Value << std::string(Crypto::GetStringFromGUID(res.GetSbGUIDFromU32Hash(sparseSet.GetDense()[sparseSet.GetSparse()[entityID]].cubemap->_textureFaceBackManifestID)));
                    
                    emitter << YAML::EndMap;
                }
                else if constexpr (std::is_same_v<T, LightComponent>) {
                    emitter << YAML::Key << "Light" << YAML::Value;
                    emitter << YAML::BeginMap;
                    
                    emitter << YAML::Key << "color" << YAML::Value;
                    emitter << YAML::Flow << YAML::BeginMap;
                    temp = sparseSet.GetDense()[sparseSet.GetSparse()[entityID]].light.color;
                    emitter << YAML::Key << "r" << YAML::Value << temp.x;
                    emitter << YAML::Key << "g" << YAML::Value << temp.y;
                    emitter << YAML::Key << "b" << YAML::Value << temp.z;
                    emitter << YAML::EndMap;
                    
                    emitter << YAML::Key << "intensity" << YAML::Value << sparseSet.GetDense()[sparseSet.GetSparse()[entityID]].light.intensity;
                    emitter << YAML::Key << "type" << YAML::Value << (int)sparseSet.GetDense()[sparseSet.GetSparse()[entityID]].light.type;
                    emitter << YAML::Key << "range" << YAML::Value << (int)sparseSet.GetDense()[sparseSet.GetSparse()[entityID]].light.range;
                    
                    emitter << YAML::EndMap;
                }
                
                else if constexpr (std::is_same_v<T, HierarchyComponent>) {
                    emitter << YAML::Key << "Hierarchy" << YAML::Value;
                    emitter << YAML::BeginMap;
                    emitter << YAML::Key << "parent" << YAML::Value << sparseSet.GetDense()[sparseSet.GetSparse()[entityID]].parent;
                    
                    emitter << YAML::Key << "children" << YAML::Value;
                    emitter << YAML::Flow << YAML::BeginMap;
                    for(Entity child : sparseSet.GetDense()[sparseSet.GetSparse()[entityID]].children) {
                        emitter << YAML::Key << "id" << YAML::Value << child;
                    }
                    emitter << YAML::EndMap;

                    emitter << YAML::EndMap;
                }
                // For asset components
                // else if constexpr (std::is_base_of_v<AssetComponentBase, T>) {
            }
        }

        void SaveScene(const String& levelName) {
            ECS::Registry& entityRegistry = ECS::Registry::GetInstance();

            String path = String("resources/levels");

            // If scene exists, delete
            if(std::filesystem::exists(std::string(path + levelName+".yaml"))) {
                std::filesystem::remove(std::string(path + levelName+".yaml"));
            }

            std::vector<DummyComponent> dummyComponentDense = entityRegistry.GetComponentStoreDense<DummyComponent>();
            YAML::Emitter emitter;
            u32 id;
            emitter << YAML::BeginMap;
            emitter << YAML::Key << "entities";

            emitter << YAML::BeginSeq;
            
            // Iterate all entities in current scene registry
            for(DummyComponent dummyComp : dummyComponentDense) {

                id = dummyComp.GetSparseIndex();
                
                emitter << YAML::BeginMap;
                emitter << YAML::Key << "id" << YAML::Value << id;
                
                // Invoke write func for each component
                std::apply([id, &emitter](auto&&... componentSparseSet) {
                    (WriteSparseSetComponentData(componentSparseSet, id, emitter), ...);
                }, entityRegistry.GetComponentStore());

                emitter << YAML::EndMap;
            }

            if(!File::Write(emitter.c_str(), path, String(levelName + ".yaml"))) {
                Log::Info("Scene: Failed to save level to ", levelName);
                return;
            }
            Log::Info("Scene: Saved level to ", path);
        }
    }
}