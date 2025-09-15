#include "SceneManagement.h"
#include "Core/Base.h"
#include "Core/Collections.h"
#include "ECS/Components.h"
#include "ECS/Registry.h"

namespace Sb {
    namespace SceneManagement {
        void SaveScene() {
            ECS::Registry& entityRegistry = ECS::Registry::GetInstance();

            std::vector<DummyComponent> dummyComponentDense = entityRegistry.GetComponentStoreDense<DummyComponent>();

            std::apply([](auto&&... componentSparseSet) {
                ([&](auto&& sparseSet) {
                    for(int i = 0; i < sparseSet.GetDense().size(); i++){
                        
                    }
                }(componentSparseSet), ...);
            }, entityRegistry.GetComponentStore());
        }
    }
}