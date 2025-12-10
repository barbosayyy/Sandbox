#include "EditorInspectorWindow.h"
#include "Core/Base.h"
#include "Core/Debug.h"
#include "ECS/Components.h"
#include "ECS/Registry.h"
#include "EditorMessage.h"
#include <string>

namespace SbEditor {

    // Inspector
    void EditorInspectorWindow::RenderBehavior() {
        if(_selectedEntityID != Sb::_MAX_U32) {
            Sb::ECS::Registry& reg = Sb::ECS::Registry::GetInstance();
            ImGui::Text("%u", _selectedEntityID);
            if(reg.GetComponentSparseSet<Sb::TransformComponent>().Contains(_selectedEntityID)) {
                ImGui::Text("Position X: %f", reg.GetComponentStoreDense<Sb::TransformComponent>()[reg.GetComponentStoreSparse<Sb::TransformComponent>()[_selectedEntityID]].localPosition.x);
                ImGui::Text("Position Y: %f", reg.GetComponentStoreDense<Sb::TransformComponent>()[reg.GetComponentStoreSparse<Sb::TransformComponent>()[_selectedEntityID]].localPosition.y);
                ImGui::Text("Position Z: %f", reg.GetComponentStoreDense<Sb::TransformComponent>()[reg.GetComponentStoreSparse<Sb::TransformComponent>()[_selectedEntityID]].localPosition.z);
            }
        }
    }

    void EditorInspectorWindow::OnMessage(const EditorMessage& msg){
        if(msg._type == EditorMessageType::SceneTreeSelect) {
            const auto& entityMsg = static_cast<const EditorSceneTreeSelectMessage&>(msg);
            _selectedEntityID = entityMsg._entityID;
        }
    }
}