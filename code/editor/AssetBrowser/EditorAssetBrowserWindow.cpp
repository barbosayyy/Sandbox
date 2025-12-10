#include "EditorAssetBrowserWindow.h"
#include "Core/Debug.h"

namespace SbEditor {

    // AssetBrowser
    void EditorAssetBrowserWindow::RenderBehavior() {
        ImGui::Text("Content");
    }

    void EditorAssetBrowserWindow::OnMessage(const EditorMessage& msg) {
        if(msg._type == EditorMessageType::SceneTreeSelect) {
            Sb::Log::Print("AssetBrowser");
        }
    }
}