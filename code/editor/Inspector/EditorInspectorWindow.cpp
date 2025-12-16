#include "EditorInspectorWindow.h"
#include "Core/Base.h"
#include "ECS/Components.h"
#include "ECS/Registry.h"
#include "EditorMessage.h"
#include "Rendering/Mesh.h"
#include "Resources/ResourceManager.h"
#include "EditorBase.h"

#include <imgui/imgui.h>
#include <string>

namespace {
    using namespace SbEditor;

    void EditorInspectorShowTransformComponent(Sb::ECS::Registry& reg, Sb::Entity entityID) {
        if(ImGui::CollapsingHeader("Transform")) {
            vec3* entityPosition = &reg.GetComponentStoreDense<Sb::TransformComponent>()[reg.GetComponentStoreSparse<Sb::TransformComponent>()[entityID]].position;
            vec3* entityRotation = &reg.GetComponentStoreDense<Sb::TransformComponent>()[reg.GetComponentStoreSparse<Sb::TransformComponent>()[entityID]].rotation;
            vec3* entityScale = &reg.GetComponentStoreDense<Sb::TransformComponent>()[reg.GetComponentStoreSparse<Sb::TransformComponent>()[entityID]].scale;

            ImGui::Text("Position: "); ImGui::SameLine();
            ImGui::PushItemWidth(80);
            ImGui::DragFloat("X##1", &entityPosition->x, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", ImGuiSliderFlags_None); ImGui::SameLine();
            ImGui::DragFloat("Y##2", &entityPosition->y, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", ImGuiSliderFlags_None); ImGui::SameLine();
            ImGui::DragFloat("Z##3", &entityPosition->z, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", ImGuiSliderFlags_None);
            ImGui::PopItemWidth();

            ImGui::Text("Rotation: "); ImGui::SameLine();
            ImGui::PushItemWidth(80);
            ImGui::DragFloat("X##4", &entityRotation->x, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", ImGuiSliderFlags_None); ImGui::SameLine();
            ImGui::DragFloat("Y##5", &entityRotation->y, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", ImGuiSliderFlags_None); ImGui::SameLine();
            ImGui::DragFloat("Z##6", &entityRotation->z, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", ImGuiSliderFlags_None);
            ImGui::PopItemWidth();

            ImGui::Text("Scale: "); ImGui::SameLine();
            ImGui::PushItemWidth(80);
            ImGui::DragFloat("X##7", &entityScale->x, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", ImGuiSliderFlags_None); ImGui::SameLine();
            ImGui::DragFloat("Y##8", &entityScale->y, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", ImGuiSliderFlags_None); ImGui::SameLine();
            ImGui::DragFloat("Z##9", &entityScale->z, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", ImGuiSliderFlags_None);
            ImGui::PopItemWidth();
        }
    }

    void EditorInspectorShowMeshComponent(Sb::ECS::Registry& reg, Sb::Entity entityID) {
        if(ImGui::CollapsingHeader("Mesh")) {
            Sb::ResourceManagement::ResourceManager& res = Sb::ResourceManagement::ResourceManager::GetInstance();
            Sb::Model* model = reg.GetComponentStoreDense<Sb::MeshComponent>()[reg.GetComponentStoreSparse<Sb::MeshComponent>()[entityID]].model;
            const char* path = res.GetAssetPathByAssetID(model->_assetID);
            ImGui::Text("Model: "); ImGui::SameLine();
            if(ImGui::Button(res.GetAssetPathByAssetID(model->_assetID).c_str())) {
                // Change model callback
            }
            ImGui::Text("Meshes: ");
            u32 i = 0;
            for(Sb::Mesh mesh : model->GetMeshes()) {
                ImGui::Text("Mesh: %u", i); ImGui::SameLine();
                ImGui::Text("Material##%u", i);
            }
        }
    }

    void EditorInspectorShowLightComponent(Sb::ECS::Registry& reg, Sb::Entity entityID) {
        if(ImGui::CollapsingHeader("Light")) {
            ImGui::Text("Color: "); ImGui::SameLine();
            // picker
            // intensity slider 0:1
            // dropdown LightType
            // range slider 0:+inf
        }
    }
    void EditorInspectorShowSkyboxComponent(Sb::ECS::Registry& reg, Sb::Entity entityID) {
        if(ImGui::CollapsingHeader("Skybox")) {
        }
    }
}

namespace SbEditor {

    // Inspector
    void EditorInspectorWindow::RenderBehavior() {
        if(_selectedEntityID != Sb::_MAX_U32) {
            Sb::ECS::Registry& reg = Sb::ECS::Registry::GetInstance();
            ImGui::Text("%u", _selectedEntityID);
            if(reg.GetComponentSparseSet<Sb::TransformComponent>().Contains(_selectedEntityID)) {
                EditorInspectorShowTransformComponent(reg, _selectedEntityID);
            }
            if(reg.GetComponentSparseSet<Sb::MeshComponent>().Contains(_selectedEntityID)) {
                EditorInspectorShowMeshComponent(reg, _selectedEntityID);
            }
            if(reg.GetComponentSparseSet<Sb::LightComponent>().Contains(_selectedEntityID)) {
                EditorInspectorShowLightComponent(reg, _selectedEntityID);
            }
            if(reg.GetComponentSparseSet<Sb::SkyboxComponent>().Contains(_selectedEntityID)) {
                EditorInspectorShowSkyboxComponent(reg, _selectedEntityID);
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