#include "Core/Debug.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "ImGuiSbContext.h"

using namespace SbEngine;

ImGuiSbContext::ImGuiSbContext() : _io(nullptr){
}

ImGuiSbContext::~ImGuiSbContext()
{
    ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiSbContext::Init(Window* window, SbImGuiStyle imGuiStyle, u8 renMode){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    _io = &ImGui::GetIO(); (void)_io;
    _io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    if(renMode & SB_OPENGL){
        InitGlfw(window->GLWindow());
    }
    else if(renMode & SB_VULKAN){
        InitVulkan();
    }
    else if(renMode & SB_DX11){
        InitDx11();
    }
    else if(renMode & SB_DX12){
        InitDx12();
    }

    switch(imGuiStyle){
        case(SbImGuiStyle::IMGUI_DARK):
            ImGui::StyleColorsDark();
        break;
        case(SbImGuiStyle::IMGUI_LIGHT):
            ImGui::StyleColorsLight();
        break;
        case(SbImGuiStyle::IMGUI_CLASSIC):
            ImGui::StyleColorsClassic();
        break;
    }

    // TODO: remove
    //bool show_demo_window = true;
    //bool show_another_window = false;
    //bool show_third_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

void ImGuiSbContext::InitGlfw(GLFWwindow* window){
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

void ImGuiSbContext::InitVulkan(){
    SB_NOT_IMPL;
}
void ImGuiSbContext::InitDx11(){
    SB_NOT_IMPL;
}
void ImGuiSbContext::InitDx12(){
    SB_NOT_IMPL;
}

void ImGuiSbContext::NewRendererFrame(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiSbContext::RenderMain(int x, int y, const char* name){
    {
        ImGui::Begin(name);
        ImGui::SetWindowPos(ImVec2(x,y), 0);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / _io->Framerate, _io->Framerate);
        ImGui::End();
    }
}

void ImGuiSbContext::RenderEnd(){
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
