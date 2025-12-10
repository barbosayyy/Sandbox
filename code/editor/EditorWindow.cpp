#include "EditorWindow.h"
#include "Core/Crypto.h"

namespace SbEditor {
    EditorWindow::EditorWindow(const char* label) : _width(100), _height(100), _label(label), _isVisible(true){
        
    }

    void EditorWindow::Render() {
        if(_isVisible) {
            if(ImGui::Begin(_label, NULL, 0)) {
                RenderBehavior();
                ImGui::End();
            }
        }
    }

    void EditorWindow::RenderBehavior() {

    }

    void EditorWindow::OnMessage(const EditorMessage& msg) {
    }
}