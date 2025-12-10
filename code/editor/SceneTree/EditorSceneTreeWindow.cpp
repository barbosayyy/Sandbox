#include "EditorSceneTreeWindow.h"
#include "Core/Base.h"
#include "ECS/Components.h"
#include "ECS/Registry.h"
#include "EditorMessage.h"
#include <imgui/imgui.h>
#include "Editor.h"
#include <string>

namespace SbEditor {

    void SceneTreeOpenEntityHierarchyNode(Sb::ECS::Registry& reg, Editor* editor, u32 entityID, ImGuiTreeNodeFlags baseFlags, bool isRoot) {
        ImGuiTreeNodeFlags nodeFlags = baseFlags;
        if(reg.GetComponentSparseSet<Sb::HierarchyComponent>().Contains(entityID) &&
            reg.GetComponentStoreDense<Sb::HierarchyComponent>()[reg.GetComponentStoreSparse<Sb::HierarchyComponent>()[entityID]].children.size() > 0) {
            // SceneTreeOpenEntityHierarchyNode(entityID, baseFlags);
            bool nodeOpen = ImGui::TreeNodeEx((void*)(intptr_t)entityID, baseFlags, "%u", entityID);
            if (ImGui::IsItemClicked()) {
                editor->GetMessageBus().DispatchWindowMessage(EditorSceneTreeSelectMessage{entityID});
            }
            if(nodeOpen) {
                ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing()); // Add indentation
                for(Sb::Entity ent : reg.GetComponentStoreDense<Sb::HierarchyComponent>()[reg.GetComponentStoreSparse<Sb::HierarchyComponent>()[entityID]].children) {
                    SceneTreeOpenEntityHierarchyNode(reg, editor, ent, baseFlags, true);
                }
                ImGui::TreePop();
                ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing()); // Remove indentation
            }
        }
        else {
            // ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());
            if(reg.GetComponentSparseSet<Sb::HierarchyComponent>().Contains(entityID) && reg.GetComponentStoreDense<Sb::HierarchyComponent>()[reg.GetComponentStoreSparse<Sb::HierarchyComponent>()[entityID]].parent != Sb::_MAX_U32 && !isRoot)
                return;
            nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
            if(ImGui::TreeNodeEx((void*)(intptr_t)entityID, nodeFlags, "%u", entityID)) {
            }
            if (ImGui::IsItemClicked()) {
                editor->GetMessageBus().DispatchWindowMessage(EditorSceneTreeSelectMessage{entityID});
            }
        }
    }

    // Scene Tree
    void EditorSceneTreeWindow::RenderBehavior() {
        Sb::ECS::Registry& reg = Sb::ECS::Registry::GetInstance();

        ImGuiTreeNodeFlags baseFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
        // if(ImGui::TreeNode())
        for(Sb::DummyComponent ent : reg.GetComponentStoreDense<Sb::DummyComponent>()) {
            SceneTreeOpenEntityHierarchyNode(reg, this->sbEditor, ent.GetSparseIndex(), baseFlags, false);
        }
    }

    void EditorSceneTreeWindow::OnMessage(const EditorMessage& msg) {
        if(msg._type == EditorMessageType::SceneTreeSelect) {
            Sb::Log::Print("Scene Tree");
        }
    }
}