#pragma once

#include "EditorWindow.h"

namespace SbEditor {
    // Scene Tree
    class EditorInspectorWindow final : public EditorWindow {
        Sb::Entity _selectedEntityID {Sb::_MAX_U32};
    protected:
        void RenderBehavior() override;
    public:
        EditorInspectorWindow() : EditorWindow("Inspector") {}
        void OnMessage(const EditorMessage& msg) override;
    };
}
