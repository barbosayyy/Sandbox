
#include "Editor.h"
#include "EditorBase.h"
#include "EditorMessage.h"
#include "EditorWindow.h"
#include "Engine/Engine.h"
#include "ImGui/ImGuiSbContext.h"
#include "Core/Debug.h"
#include "EditorGameService.h"
#include "SceneTree/EditorSceneTreeWindow.h"
#include "Inspector/EditorInspectorWindow.h"
#include "AssetBrowser/EditorAssetBrowserWindow.h"

#include "imgui/imgui.h"
#include <memory>

namespace SbEditor {

    Editor::Editor(Sb::IEngine* sbEngine) : _uiVisibilityFlags(0){
        _sbEnginePtr = sbEngine;
    }

    void Editor::Start() {
        this->_sbImGuiContext = &_sbEnginePtr->GetRenderer().GetImGuiSbContext();
        this->_editorGlobalWindowWidth = _sbEnginePtr->GetRenderer().GetWindow()->GetWindowWidth();
        this->_editorGlobalWindowHeight = _sbEnginePtr->GetRenderer().GetWindow()->GetWindowHeight();
        this->UISetElementsVisible(SB_EDITORUI_MENU);

        ImFont* fontEditor = this->_sbImGuiContext->_io->Fonts->AddFontFromFileTTF(SB_EDITORUI_FONTS_DIR+"Roboto/Roboto.ttf", 16, NULL, this->_sbImGuiContext->_io->Fonts->GetGlyphRangesDefault());
        if(fontEditor != nullptr){
            this->_sbImGuiContext->_io->Fonts->Build();
            _sbImGuiContext->_io->FontDefault = fontEditor;
        }
        else {
            Sb::Log::Warn("Editor: Failed to load custom font");
        }

        AddEditorWindow(std::make_unique<EditorSceneTreeWindow>());
        AddEditorWindow(std::make_unique<EditorInspectorWindow>());
        AddEditorWindow(std::make_unique<EditorAssetBrowserWindow>());
    }

    void Editor::Update() {
        if(this->_editorGlobalWindowWidth != _sbEnginePtr->GetRenderer().GetWindow()->GetWindowWidth())
            this->_editorGlobalWindowWidth = _sbEnginePtr->GetRenderer().GetWindow()->GetWindowWidth();
        if(this->_editorGlobalWindowHeight != _sbEnginePtr->GetRenderer().GetWindow()->GetWindowHeight())
            this->_editorGlobalWindowHeight = _sbEnginePtr->GetRenderer().GetWindow()->GetWindowHeight();
    }

    void Editor::Render() {
        this->UIRender();
    }

    void Editor::Stop() {
        this->UISetElementsVisible(0);
        _messageBus.UnsubscribeAll();
        _windows.clear();
    }

    void Editor::StartProjectManager() {
        this->_sbEnginePtr->InitContext("Sandbox Project Manager", *this);
    }

    void Editor::StartEditor() {
        this->_sbEnginePtr->InitContext("Sandbox Editor", *this);
    }

    void Editor::AddEditorWindow(std::unique_ptr<EditorWindow> win) {
        _messageBus.SubscribeWindow(EditorMessageType::SceneTreeSelect, win.get());
        _messageBus.SubscribeWindow(EditorMessageType::AssetBrowserSelect, win.get());
        win->sbEditor = this;
        _windows.push_back(std::move(win));
    }

    void Editor::UIRender() {
        if(this->_uiVisibilityFlags & SB_EDITORUI_MENU) {
            this->UIShowMenu();
        }

        for(auto& win : _windows) {
            win->Render();
        }
    }
    
    void Editor::UIShowMenu() {
        if(ImGui::BeginMainMenuBar()) {
            if(ImGui::BeginMenu("File")) {
                if(ImGui::MenuItem("New")) {}
                if(ImGui::MenuItem("Open")) {EditorGameService::LoadSbGame();}
                if(ImGui::MenuItem("Save")) {}
                ImGui::EndMenu();
            }
            if(ImGui::BeginMenu("Edit")) {
                if(ImGui::MenuItem("Undo")) {}
                if(ImGui::MenuItem("Redo")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }
}
