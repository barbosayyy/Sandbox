#pragma once

#include "Core/Types.h"
#include "Core/Base.h"
#include "Core/Singleton.h"
#include "Core/Collections.h"
#include "ECS/Components.h"
#include <tuple>
#include <unordered_map>

namespace Sb {
    namespace ECS {
        class Registry final : public Singleton<Registry, int> {
            using CoreComponents = std::tuple<
                DummyComponent,
                TransformComponent,
                MeshComponent,
                SkyboxComponent,
                LightComponent,
                HierarchyComponent,
                ScriptComponent
            >;

            template <typename Tuple>
            struct SparseSetCoreComponentTuple;
            template <typename... Components>
            struct SparseSetCoreComponentTuple<std::tuple<Components...>>{
                using type = std::tuple<SparseSet<Components>...>;
            };
            using CoreComponentStore = SparseSetCoreComponentTuple<CoreComponents>::type;

        public:

            Registry();
            ~Registry();

            // template<typename T>
            // bool HasComponent() {
            //     return(std::is_same<T, CoreComponents>);
            // }

            template<typename T>
            void AddComponent(u32 entityID) { std::get<SparseSet<T>>(_componentStore).Insert(entityID, T{}); };
            template<typename T>
            void RemoveComponent(u32 entityID) { std::get<SparseSet<T>>(_componentStore).Remove(entityID); };
            
            template<typename T>
            T& GetComponent(u32 entityID) { return std::get<SparseSet<T>>(_componentStore).Get(entityID); }

            void RemoveAllComponents(u32 entity) { std::apply([entity](auto&... componentSparseSet) { (componentSparseSet.Remove(entity), ...); }, _componentStore); }

            u32 GetNextEntityID() const { return _nextEntityId; }

            void IncrementNextEntityID() { _nextEntityId++;}

            void Clear() { std::apply([](auto&... componentSparseSet) { (componentSparseSet.Clear(), ...); }, _componentStore); _nextEntityId = 0; Log::Info("ECS Registry: Cleared all data"); }

            template<typename T>
            std::vector<T>& GetComponentStoreDense() { return std::get<SparseSet<T>>(_componentStore).GetDense(); }

            template<typename T>
            std::vector<u32>& GetComponentStoreSparse() { return std::get<SparseSet<T>>(_componentStore).GetSparse(); }
            template<typename T>
            SparseSet<T>& GetComponentSparseSet() { return std::get<SparseSet<T>>(_componentStore); }

            CoreComponentStore& GetComponentStore() { return _componentStore; }

            void EmplaceEntityGUID(SbGUID newGUID, u32 entityID) { _guidSparseIndex.emplace(newGUID, entityID); }; 

        private:

            CoreComponentStore _componentStore;
            std::unordered_map<SbGUID, u32> _guidSparseIndex;
            u32 _nextEntityId;
        };
    }
}