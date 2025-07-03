#include "Engine/Engine.h"
#include "Core/Base.h"
#include "Core/Debug.h"
#include "Input/Input.h"
#include "glfw/glfw3.h"
#include "imgui/imgui.h"

using namespace SbEngine;

bool Engine::_error = false;

Engine::Engine() {
    SetRenderer(Renderer::GetInstance());
    SetInputManager(InputManager::GetInstance(this->_renderer->GetWindow()->GLWindow()));
    // _imGuiManager = new ImGuiManager();
}

Engine::~Engine() {}

void Engine::SetRenderer(Renderer& renderer) {
    _renderer = &renderer;
}

void Engine::SetInputManager(InputManager& inputManager) {
    _internalInput = &inputManager;
}

bool Engine::Validate(){
    bool flag = true;

    if(_renderer == nullptr)
        flag = false;

    if(_internalInput == nullptr)
        flag = false;

    if(_error == true)
        flag = false;

    if(glfwWindowShouldClose(_renderer->GetWindow()->GLWindow())){
        flag = false;
    }

    if(!flag){
        Logger::Error("Engine: Component validation failed, stopping...");
    }

    return flag;
}

void Engine::Start(){
    Camera* camera = new Camera(0.0f, 0.0f, -3.0f);
    _renderer->SetRenderCamera(camera);
    _renderer->GetRenderCamera()->_moveSpeed = 0.025;

    this->GetRenderer().Setup();

    #ifdef SB_BUILD
        Logger::SetLogLevel(LogLevel::INFO);
    #elif SB_RELEASE
        Logger::SetLogLevel(LogLevel::ERROR);
    #endif
    
    InputManager::GetInstance().AddInputFunction([this]() {OnInput(); });

    Logger::Print("SbEng: Finished start");
}

void Engine::Update(){
    _internalInput->ProcessInput();
}

void Engine::BeginNewFrame(){
    this->GetRenderer().OnBeginFrame();
}

void Engine::Render(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    _renderer->GetImGuiSbContext().RenderMain(1, 2, "Sandbox", _renderer->_faceAmount, _renderer->renderMode);
    _renderer->GetImGuiSbContext().RenderEnd();

    glfwPollEvents();
    glfwSwapBuffers(_renderer->GetWindow()->GLWindow());
}

void Engine::Stop(){
    _renderer = nullptr;
    _internalInput = nullptr;
    // delete _sceneManager;
}

void Engine::OnInput()
{
    if(InputManager::PressedKey(SB_KEYBOARD_1)){
        _renderer->renderMode = 1;
    }
    else if(InputManager::PressedKey(SB_KEYBOARD_2)){
    _renderer->renderMode = 2;
    }
    else if(InputManager::PressedKey(SB_KEYBOARD_3)){
        _renderer->renderMode = 3;
    }
}
