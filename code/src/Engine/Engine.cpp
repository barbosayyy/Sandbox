#include "Engine/Engine.h"
#include "Core/Base.h"
#include "Core/Debug.h"
#include "Input/Input.h"
#include "glfw/glfw3.h"
#include "imgui/imgui.h"

using namespace Sb;

bool Engine::_error = false;

Engine::Engine() : _uiRenderEnabled(true){
	SetRenderer(Renderer::GetInstance());
	SetInputManager(InputManager::GetInstance(this->_renderer->GetWindow()->GLWindow()));
}

Engine::~Engine() {
}

void Engine::SetRenderer(Renderer& renderer) {
	_renderer = &renderer;
}

void Engine::SetInputManager(InputManager& inputManager) {
	_internalInput = &inputManager;
}

bool Engine::Validate() {

	if(_error == true)
		return false;

	if(glfwWindowShouldClose(_renderer->GetWindow()->GLWindow())) {
		Log::Info("Engine: Window closed...");
		return false;
	}

	return true;
}

void Engine::Start() {
	Camera* camera = new Camera(0.0f, 0.0f, -3.0f);
	_renderer->SetRenderCamera(camera);
	_renderer->GetRenderCamera()->_moveSpeed = 0.025;

	this->GetRenderer().Setup();

#ifdef SB_DEBUG
	Log::SetLogLevel(Log::Level::DEBUG);
#elif SB_RELEASE
	Log::SetLogLevel(Log::Level::WARN);
#endif

	InputManager::GetInstance().AddInputFunction([this]() { OnInput(); });

	Log::Info("Engine: Started");
}

void Engine::Update() {
	_internalInput->ProcessInput();
	// TEMP
	if(_renderer->GetStateDirtyFlags() & SB_DIRTY_PROJECTION) {
		_renderer->GetRenderCamera()->GenerateProjection(_renderer->GetViewportWidth(), _renderer->GetViewportHeight());
		_renderer->ClearStateDirtyFlags(SB_DIRTY_PROJECTION);
	}
}

void Engine::BeginNewFrame() {
	this->GetRenderer().OnBeginFrame();
}

void Engine::Render() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if(_uiRenderEnabled)
		_renderer->GetImGuiSbContext().RenderMain(1, 2, "Sandbox", _renderer->_faceAmount, _renderer->_stateShowBufferMask);
	_renderer->GetImGuiSbContext().RenderEnd();

	glfwPollEvents();
	glfwSwapBuffers(_renderer->GetWindow()->GLWindow());
}

void Engine::Stop() {
	Log::Info("Engine: Stopping...");
	_renderer	   = nullptr;
	_internalInput = nullptr;
	// delete _sceneManager;
}

void Engine::OnInput() {
	if(InputManager::PressedKey(SB_KEYBOARD_1)) {
		_renderer->_stateShowBufferMask = 1;
	} else if(InputManager::PressedKey(SB_KEYBOARD_2)) {
		_renderer->_stateShowBufferMask = 2;
	} else if(InputManager::PressedKey(SB_KEYBOARD_3)) {
		_renderer->_stateShowBufferMask = 3;
	}
}
