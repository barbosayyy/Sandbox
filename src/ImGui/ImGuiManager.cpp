#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "ImGuiManager.h"

ImGuiManager::ImGuiManager() : _io(nullptr){
}

ImGuiManager::~ImGuiManager()
{
    ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiManager::Init(GLFWwindow* window, SandboxImGuiStyle imGuiStyle){
    IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		_io = &ImGui::GetIO(); (void)_io;
		_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        // TODO this will require checking for renderer type
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init();
        switch(imGuiStyle){
            case(SandboxImGuiStyle::IMGUI_DARK):
		        ImGui::StyleColorsDark();
            break;
            case(SandboxImGuiStyle::IMGUI_LIGHT):
                ImGui::StyleColorsLight();
            break;
            case(SandboxImGuiStyle::IMGUI_CLASSIC):
                ImGui::StyleColorsClassic();
            break;
        }
		//bool show_demo_window = true;
		//bool show_another_window = false;
		//bool show_third_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

void ImGuiManager::NewRendererFrame(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiManager::RenderMain(){
    {
        static float f = 0.0f;
        static int counter = 0;
        ImGui::Begin("Sandbox");
        ImGui::SetWindowPos(ImVec2(1,2), 0);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / _io->Framerate, _io->Framerate);
        ImGui::Text("Tris: %d", 0);
        ImGui::End();
    }
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
