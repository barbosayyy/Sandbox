#include "Editor.h"
#include "Engine/Engine.h"
#include "ImGui/ImGuiSbContext.h"
#include "Core/Debug.h"
#include "imgui/imgui.h"

namespace SbEditor {
    void Editor::Run() {
        Sb::Engine sbEngine;
        sbEngine.Start();

#ifdef SB_EDITOR
    sbEngine.GetRenderer().GetWindow()->SetWindowTitle("Sandbox Editor");
#endif

        this->Setup(&sbEngine);

        sbEngine.SetUIRenderingEnabled(false);

        while(sbEngine.Validate() && !this->ShouldStop()) {
            sbEngine.Update();
            sbEngine.BeginNewFrame();
            
            this->Update();
            this->Render();

            sbEngine.Render();
        }

        sbEngine.Stop();
    }

    void Editor::Setup(Sb::IEngine* sbEngine) {
        this->_sbEnginePtr = sbEngine;
        this->_sbImGuiContext = &_sbEnginePtr->GetRenderer().GetImGuiSbContext();
        this->_editorWindowWidth = sbEngine->GetRenderer().GetWindow()->GetWindowWidth();
        this->_editorWindowHeight = sbEngine->GetRenderer().GetWindow()->GetWindowHeight();
        this->UISetElementsVisible(SB_EDITORUI_MENU | SB_EDITORUI_SCENETREE | SB_EDITORUI_ASSETEXPLORER | SB_EDITORUI_ASSETTREE | SB_EDITORUI_INSPECTOR);
    }

    void Editor::Update() {
        if(this->_editorWindowWidth != _sbEnginePtr->GetRenderer().GetWindow()->GetWindowWidth())
            this->_editorWindowWidth = _sbEnginePtr->GetRenderer().GetWindow()->GetWindowWidth();
        if(this->_editorWindowHeight != _sbEnginePtr->GetRenderer().GetWindow()->GetWindowHeight())
            this->_editorWindowHeight = _sbEnginePtr->GetRenderer().GetWindow()->GetWindowHeight();
    }

    void Editor::Render() {
        this->UIRender();
    }

    void Editor::Stop() {
        this->_sbEnginePtr = nullptr;
        this->_sbImGuiContext = nullptr;
    }

    void Editor::UIRender() {
        if(this->_uiVisibilityFlags & SB_EDITORUI_SCENETREE) {
            this->UIShowMenu();
        }
        if(this->_uiVisibilityFlags & SB_EDITORUI_SCENETREE) {
            this->UIShowSceneTree();
        }
        
        if(this->_uiVisibilityFlags & SB_EDITORUI_ASSETTREE) {
            this->UIShowAssetTree();
        }

        if(this->_uiVisibilityFlags & SB_EDITORUI_ASSETEXPLORER) {
            this->UIShowAssetExplorer();
        }
        
        if(this->_uiVisibilityFlags & SB_EDITORUI_INSPECTOR) {
            this->UIShowInspector();
        }
    }
    
    void Editor::UIShowMenu() {
        ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
        ImGui::SetWindowPos(ImVec2(0,0), 0);
        ImGui::SetWindowSize(ImVec2(_editorWindowWidth, 60));
        ImGui::End();
    }

    void Editor::UIShowSceneTree() {
        int windowHeight = 60;
        int assetExplorerHeight = _editorWindowHeight*0.3;
        ImGui::Begin("Scene Tree", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
        ImGui::SetWindowPos(ImVec2(0, windowHeight), 0);
        ImGui::SetWindowSize(ImVec2(_editorWindowWidth*0.20, _editorWindowHeight-windowHeight-assetExplorerHeight), 0);
        ImGui::End();
    }

    void Editor::UIShowAssetTree() {
        ImGui::Begin("Asset Tree", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
        ImGui::SetWindowPos(ImVec2(0, _editorWindowHeight-_editorWindowHeight*0.3), 0);
        ImGui::SetWindowSize(ImVec2(_editorWindowWidth*0.20, _editorWindowHeight*0.3), 0);
        ImGui::End();
    }

    void Editor::UIShowAssetExplorer() {
        ImGui::Begin("Asset Explorer", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
        ImGui::SetWindowPos(ImVec2(_editorWindowWidth*0.20, _editorWindowHeight-_editorWindowHeight*0.3), 0);
        ImGui::SetWindowSize(ImVec2(_editorWindowWidth-_editorWindowWidth*0.20, _editorWindowHeight*0.3), 0);
        ImGui::End();
    }

    void Editor::UIShowInspector() {
        int windowHeight = 60;
        int assetExplorerHeight = _editorWindowHeight*0.3;
        ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
        ImGui::SetWindowPos(ImVec2(_editorWindowWidth-(_editorWindowWidth*0.20), windowHeight), 0);
        ImGui::SetWindowSize(ImVec2(_editorWindowWidth*0.20, _editorWindowHeight-windowHeight-assetExplorerHeight), 0);
        ImGui::End();
    }
}
