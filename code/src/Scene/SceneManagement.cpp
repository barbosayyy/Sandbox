#include "Core/Base.h"

#include "SceneManagement.h"

#include "Core/Collections.h"
#include "ECS/Components.h"
#include "ECS/Registry.h"

#include "Resources/ResourceManager.h"
#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"

namespace Sb {
    namespace SceneManagement {
        
        template <typename T>
        void WriteSparseSetComponentData(SparseSet<T>& sparseSet, u32 entityID, YAML::Emitter& emitter) {
            if(sparseSet.Contains(entityID)) {

                vec3 temp;

                if constexpr (std::is_same_v<T, TransformComponent>) {
                    emitter << YAML::Key << "Transform" << YAML::Value;
                    emitter << YAML::BeginMap;

                    emitter << YAML::Key << "position" << YAML::Value;
                    emitter << YAML::Flow << YAML::BeginMap;
                    temp = sparseSet.GetDense()[sparseSet.GetSparse()[entityID]].pos;
                    emitter << YAML::Key << "x" << YAML::Value << temp.x;
                    emitter << YAML::Key << "y" << YAML::Value << temp.y;
                    emitter << YAML::Key << "z" << YAML::Value << temp.z;
                    emitter << YAML::EndMap;
                    
                    emitter << YAML::Key << "rotation" << YAML::Value;
                    emitter << YAML::Flow << YAML::BeginMap;
                    temp = sparseSet.GetDense()[sparseSet.GetSparse()[entityID]].rot;
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

                    // emitter << YAML::Key << "id" << YAML::Value << manifestID;

                    emitter << YAML::EndMap;
                }
            }
        }

        static void SaveScene(const String& levelName) {
            ECS::Registry& entityRegistry = ECS::Registry::GetInstance();
            std::vector<DummyComponent> dummyComponentDense = entityRegistry.GetComponentStoreDense<DummyComponent>();
            YAML::Emitter emitter;
            u32 id;
            emitter << YAML::BeginMap;
            emitter << YAML::Key << "entities";

            emitter << YAML::BeginSeq;
            
            for(DummyComponent dummyComp : dummyComponentDense) {

                id = dummyComp.sparseIndex;
                
                emitter << YAML::BeginMap;
                emitter << YAML::Key << "id" << YAML::Value << id;
                
                std::apply([id, &emitter](auto&&... componentSparseSet) {
                    (WriteSparseSetComponentData(componentSparseSet, id, emitter), ...);
                }, entityRegistry.GetComponentStore());

                emitter << YAML::EndMap;
            }

            String path = String(File::GetCurrentDirectory() + "\\resources\\levels");

            if(!File::Write(emitter.c_str(), path, String(levelName + ".yaml"))) {
                Log::Info("Scene: Failed to save level to ", levelName);
                return;
            }
            Log::Info("Scene: Saved level to ", path);

        }
    }
}