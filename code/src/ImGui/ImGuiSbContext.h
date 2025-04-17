#pragma once

#include "Core/Base.h"
#include "Rendering/Window.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace SbEngine{

    enum class SbImGuiStyle {
        IMGUI_DARK,
        IMGUI_LIGHT,
        IMGUI_CLASSIC
    };

    class ImGuiSbContext{
        public:
            ImGuiSbContext();
            ~ImGuiSbContext();
            void Init(Window* window, SbImGuiStyle imGuiStyle, u8 renMode);
            void NewRendererFrame();
            void RenderMain(int x, int y, const char* name);
            void RenderEnd();
            ImGuiIO* _io;
        protected:
            
        private:
            void InitGlfw(GLFWwindow* window);
            void InitVulkan();
            void InitDx12();
            void InitDx11();
    };
}