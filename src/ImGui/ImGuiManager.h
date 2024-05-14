#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

enum class SandboxImGuiStyle {
    IMGUI_DARK,
    IMGUI_LIGHT,
    IMGUI_CLASSIC
};

class ImGuiManager{
    public:
        ImGuiManager();
        ~ImGuiManager();
        void Init(GLFWwindow* window, SandboxImGuiStyle imGuiStyle);
        void NewRendererFrame();
        void RenderMain();
        ImGuiIO* _io;              
    private:
};