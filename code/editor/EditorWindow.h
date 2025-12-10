#pragma once
#include "Core/Types.h"
#include "EditorBase.h"
#include "EditorMessage.h"
#include "imgui/imgui.h"

namespace SbEditor {
    class Editor;

    class EditorWindow {
    protected:
        virtual void RenderBehavior();
        
        // Sb::SbGUID _windowID;
        u32 _width;
        u32 _height;
        ImGuiWindowFlags _flags;
        const char* _label;
        bool _isVisible;
        
    public:
        EditorWindow(const char* label);
        virtual ~EditorWindow() = default;
        
        virtual void Render();
        
        virtual void OnMessage(const EditorMessage& msg);
        
        // Sb::SbGUID GetWindowID() {return _windowID;};
        u32 GetHeight() const {return _height;};
        u32 GetWidth() const {return _width;};
        void SetHeight(u32 height) {_height = height;}
        void SetWidth(u32 width) {_width = width;}
        void IsVisible(bool visible) {_isVisible = visible;};
        
        Editor* sbEditor;
    };
}
