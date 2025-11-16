#include "Engine/Engine.h"
#include "Core/Base.h"
#include "Core/Debug.h"
#include "ECS/Components.h"
#include "ECS/Registry.h"
#include "Input/Input.h"
#include "Resources/ResourceManager.h"
#include "glfw/glfw3.h"
#include "imgui/imgui.h"
#include "Core/Profiler.h"
#include "Scene/SceneManagement.h"

#include "ECS/Systems/InputSystem.h"
#include "ECS/Systems/PhysicsSystem.h"
#include "ECS/Systems/HierarchySystem.h"
#include <memory>

using namespace Sb;

bool Engine::_error = false;

Engine::Engine() : _uiRenderEnabled(true), _firstFrame(true){

	Log::Info("Starting Sandbox application backend");

#ifdef SB_BUILD_DEBUG
	Log::SetLogLevel(Log::Level::DEBUG);
#elif SB_BUILD_RELEASE
	Log::SetLogLevel(Log::Level::WARNING);
#endif

	SetRenderer(Renderer::GetInstance());
	SetInputManager(InputManager::GetInstance(this->_renderer->GetWindow()->GLWindow()));
	SetECSRegistry(ECS::Registry::GetInstance());
	SetResourceManager(ResourceManagement::ResourceManager::GetInstance());
}

Engine::~Engine() {
}

void Engine::SetRenderer(Renderer& renderer) {
	_renderer = &renderer;
}

void Engine::SetInputManager(InputManager& inputManager) {
	_internalInput = &inputManager;
}

void Engine::SetECSRegistry(ECS::Registry& registry) {
	_ecsRegistry = &registry;
}

void Engine::SetResourceManager(ResourceManagement::ResourceManager& resourceManager) {
	_resourceManager = &resourceManager;
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

	// Systems run-time setup

	Camera* camera = new Camera(0.0f, 0.0f, -3.0f);
	_renderer->SetRenderCamera(camera);
	_renderer->GetRenderCamera()->_moveSpeed = 0.025;

	this->GetRenderer().Setup();

	InputManager::GetInstance().AddInputFunction([this]() { OnInput(); });
	
	Log::Info("Engine: Started");
}

void Engine::Update() {

	if(_firstFrame) {
		Log::Info(_ecsRegistry->GetComponentStoreDense<DummyComponent>().size(), " Entities");
		Log::Info(_ecsRegistry->GetComponentStoreDense<TransformComponent>().size(), " Transform components");
		Log::Info(_ecsRegistry->GetComponentStoreDense<MeshComponent>().size(), " Mesh components");
		Log::Info(_ecsRegistry->GetComponentStoreDense<SkyboxComponent>().size(), " Skybox components");
		Log::Info(_ecsRegistry->GetComponentStoreDense<LightComponent>().size(), " Light components");
		Log::Info(_ecsRegistry->GetComponentStoreDense<HierarchyComponent>().size(), " Hierarchy components");
		Log::Info("Rendering first frame");

		_firstFrame = false;
	}

	Profiler::StopRecord("Frame swap");
	Profiler::DisableFrameCapture();

	ECS::InputSystem::Update(*this->_ecsRegistry);
	ECS::PhysicsSystem::Update(*this->_ecsRegistry);
	ECS::HierarchySystem::Update(*this->_ecsRegistry);

	_internalInput->ProcessInput();
	
	// TEMP
	if(_renderer->GetStateDirtyFlags() & SB_DIRTY_PROJECTION) {
		_renderer->GetRenderCamera()->GenerateProjection(_renderer->GetViewportWidth(), _renderer->GetViewportHeight());
		_renderer->ClearStateDirtyFlags(SB_DIRTY_PROJECTION);
	}
}

void Engine::Render() {
	Profiler::StartRecord("Render");
	_renderer->OnBeginFrame();
	for(std::unique_ptr<RenderPass>& pass : _renderer->GetRenderpasses()) {
		pass->Execute();
	}
}

void Engine::LateRender() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	Profiler::StopRecord("Render");
	
	// Game-side Engine UI
	if(_uiRenderEnabled)
		_renderer->GetImGuiSbContext().RenderMain(1, 2, "Sandbox", _renderer->_faceAmount, _renderer->_stateShowBufferMask);
	_renderer->GetImGuiSbContext().RenderEnd();

	Profiler::SetTotalFrametime(_renderer->GetImGuiSbContext()._io->Framerate);

	Profiler::StartRecord("Frame swap");
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
		_renderer->_stateShowBufferMask = 0;
	} else if(InputManager::PressedKey(SB_KEYBOARD_2)) {
		_renderer->_stateShowBufferMask = 1;
	} else if(InputManager::PressedKey(SB_KEYBOARD_3)) {
		_renderer->_stateShowBufferMask = 2;
	} else if(InputManager::PressedKey(SB_KEYBOARD_4)) {
		_renderer->_stateShowBufferMask = 3;
	} else if(InputManager::PressedKey(SB_KEYBOARD_F5)) {
		Profiler::EnableFrameCapture();
	} else if(InputManager::PressedKey(SB_KEYBOARD_F6)) {
		Profiler::ClearRecordings();
	} else if(InputManager::PressedKey(SB_KEYBOARD_F7)) {
		Profiler::DumpRecordings();
	} else if(InputManager::PressedKey(SB_KEYBOARD_L)) {
		SceneManagement::SaveScene("level1");
	}
}
