#include "Rendering/Renderer.h"
#include "Core/Base.h"
#include "Core/Debug.h"
#include "Core/Config.h"
#include "Core/Types.h"
#include "ImGui/ImGuiSbContext.h"

using namespace SbEngine;

Renderer::Renderer() : _apiMode(0x0), _screenWidth(DEFAULT_WINDOW_WIDTH), _screenHeight(DEFAULT_WINDOW_HEIGHT){
	_apiMode |= SB_OPENGL;

	Logger::Print("Starting Sandbox Renderer, Mode: ", static_cast<int>(_apiMode));

	if(_apiMode & SB_OPENGL){
		if (!glfwInit())
		{
			SB_ASSERT("Failed to initialize GLFW.");
		}
		_windowHandle = new Window("Sandbox", DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
		if (!_windowHandle->GLWindow())
		{
			glfwTerminate();
			SB_ASSERT("Failed to create window.");
		}
		// GLEW initialization
		if (glewInit() != GLEW_OK)
		{
			glfwTerminate();
			SB_ASSERT("Failed to initialize GLEW.");
		}
		else{
			Logger::Print("Renderer: Init OGL");
		}
	}
	else if(_apiMode & SB_VULKAN){
		SB_NOT_IMPL;
	}
	else if(_apiMode & SB_DX11){
		SB_NOT_IMPL;
	}
	else if(_apiMode & SB_DX12){
		SB_NOT_IMPL;
	}

	_shaderManager.Init();

	_imGuiSbContext = new ImGuiSbContext();
}

Renderer::~Renderer(){
	delete _renderCamera;
    delete _windowHandle;
	delete _imGuiSbContext;

	if(_apiMode & SB_OPENGL)
		glfwTerminate();
}

mat4 Renderer::GetProjection(){
	if(this->GetRenderCamera()->GetProjectionMode() == CameraProjectionMode::CAMERA_PROJECTION_PERSPECTIVE){
		return glm::perspective(glm::radians(60.0f), (float)this->GetWindow()->GetWidth() / (float)this->GetWindow()->GetHeight(), this->GetRenderCamera()->_near, this->GetRenderCamera()->_far);
	}
	else{ // WIP: CAMERA_PROJECTION_ORTHO
		SB_NOT_IMPL;
	}
	return mat4(1.0f);
}

void Renderer::Setup(){
	_imGuiSbContext->Init(this->_windowHandle, SbImGuiStyle::IMGUI_DARK,this->_apiMode);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT, GL_FILL);
}

void Renderer::OnBeginFrame(){
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GetImGuiSbContext().NewRendererFrame();
}
