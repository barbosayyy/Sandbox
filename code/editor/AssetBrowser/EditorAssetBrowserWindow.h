#pragma once

#include "EditorWindow.h"

namespace SbEditor {
    // Scene Tree
    class EditorAssetBrowserWindow final : public EditorWindow {
    protected:
        void RenderBehavior() override;
    public:
        EditorAssetBrowserWindow() : EditorWindow("Asset Browser") {}
        void OnMessage(const EditorMessage& msg) override;
    };
}
