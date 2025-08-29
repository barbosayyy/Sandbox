#include "Core/Base.h"
#include "ECS/Components.h"

#include "Core/Collections.h"

namespace Sb {

    template<typename... Components>
    class ComponentManager {
    public:
        template<typename T>
        constexpr bool HasComponent() {
            return(std::is_same_v<T, Components> || ...);
        }

        template<typename T>
        void AddComponent(u32 entityID) { std::get<SparseSet<T>>(_componentStore).Insert(entityID, T{}); };
        template<typename T>
        void RemoveComponent(u32 entityID) { std::get<SparseSet<T>(_componentStore).Remove(entityID)>; };
        
        void RemoveAllComponents(u32 entity) { std::apply([entity](auto&... componentSparseSet) { (componentSparseSet.Remove(entity), ...); }, _componentStore); }
        
#ifdef SB_DEBUG
        template<typename T>
        std::vector<T> GetComponentStoreDense() const { return std::get<SparseSet<T>>(_componentStore).GetDense(); }
        template<typename T>
        std::vector<u32> GetComponentStoreSparse() const { return std::get<SparseSet<T>>(_componentStore).GetSparse(); }
        template<typename T>
        SparseSet<T> GetSparseSet() const { return std::get<SparseSet<T>>(_componentStore); }
#endif

    private:
        std::tuple<SparseSet<Components>...> _componentStore;
    };
}