#pragma once

#include "Core/Base.h"
#include "Core/Singleton.h"
#include "Core/Collections.h"
#include "ECS/Components.h"

namespace Sb {
    namespace ECS {
        class Registry final : public Singleton<Registry, int> {
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
            
            void RemoveAllComponents(u32 entity) { std::apply([entity](auto&... componentSparseSet) { (componentSparseSet.Remove(entity), ...); }, _componentStore); }

            u32 GetNextEntityID() const { return _nextEntityId; }

            void IncrementNextEntityID() { _nextEntityId++;}

#ifdef SB_DEBUG
            template<typename T>
            std::vector<T> GetComponentStoreDense() const { return std::get<SparseSet<T>>(_componentStore).GetDense(); }
            template<typename T>
            std::vector<u32> GetComponentStoreSparse() const { return std::get<SparseSet<T>>(_componentStore).GetSparse(); }
            template<typename T>
            SparseSet<T> GetComponentSparseSet() const { return std::get<SparseSet<T>>(_componentStore); }
#endif
        private:
            using CoreComponents = std::tuple<
                DummyComponent,
                TransformComponent,
                MeshComponent
            >;

            template <typename Tuple>
            struct SparseSetCoreComponentTuple;
            template <typename... Components>
            struct SparseSetCoreComponentTuple<std::tuple<Components...>>{
                using type = std::tuple<SparseSet<Components>...>;
            };
            using CoreComponentStore = SparseSetCoreComponentTuple<CoreComponents>::type;

            CoreComponentStore _componentStore;
            u32 _nextEntityId;
        };
    }
}