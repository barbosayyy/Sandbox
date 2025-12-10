#pragma once

#include "EditorWindow.h"

namespace SbEditor {
    // Scene Tree
    class EditorSceneTreeWindow final : public EditorWindow {
    protected:
        void RenderBehavior() override;
    public:
        EditorSceneTreeWindow() : EditorWindow("Scene Tree") {}
        void OnMessage(const EditorMessage& msg) override;
    };
}
