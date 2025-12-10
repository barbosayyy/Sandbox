#include "EditorGameService.h"
#include "Core/Base.h"
#include "ECS/Components.h"
#include "ECS/Registry.h"
#include "ECS/EntityManagement.h"

namespace SbEditor {
    void EditorGameService::CompileSbGameProject() {
        // Game is compiled into DLL/SO
    }
    void EditorGameService::LoadSbGame() {

        // DLL/SO should be loaded here
        
        // Temp
        Sb::Entity ent0 = Sb::AddEntity();
        Sb::Entity ent1 = Sb::AddEntity();
        Sb::Entity ent2 = Sb::AddEntity();
        Sb::Entity ent3 = Sb::AddEntity();

        Sb::AddEntityComponent<Sb::HierarchyComponent>(ent2);
        Sb::AddEntityComponent<Sb::HierarchyComponent>(ent3);

        Sb::GetEntityComponent<Sb::HierarchyComponent>(ent2).AddChild(ent3);

        Sb::AddEntityComponent<Sb::TransformComponent>(ent0);
    };
}