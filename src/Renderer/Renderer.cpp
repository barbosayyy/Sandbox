#include "Renderer.h"
#include "../Core/Debug.h"
#include "Shader.h"
#include <iostream>

using namespace Sandbox;

Renderer::Renderer() : _renMode(0x0), _screenWidth(DEFAULT_SCREEN_W), _screenHeight(DEFAULT_SCREEN_H){
	if(_instance == nullptr){
		_instance = this;

		_renMode |= RENDERER_OPENGL;
		Logger::Trace(LogLevel::RUNTIME, "Starting Sandbox Renderer, Mode: ", static_cast<int>(_renMode));
		if(_renMode & RENDERER_OPENGL){
			if (!glfwInit())
			{
				SB_ASSERT("Failed to initialize GLFW.");
			}
			_windowHandle = new Window("Sandbox", WINDOW_WIDTH, WINDOW_HEIGHT);
			if (!_windowHandle->GLWindow())
			{
				glfwTerminate();
				SB_ASSERT("Failed to find window.");
			}
			// GLEW initialization
			if (glewInit() != GLEW_OK)
			{
				glfwTerminate();
				SB_ASSERT("Failed to initialize GLEW.");
			}
		}
		else if(_renMode & RENDERER_VULKAN){
			SB_ASSERT("Vulkan isn't ready yet!");
		}
		else if(_renMode & RENDERER_DX12){
			std::cout << "A";
			SB_ASSERT("DirectX isn't ready yet!");
		}
	}
}

Renderer::~Renderer()
{
    delete _windowHandle;
}

mat4 Renderer::GetProjection()
{
	if(this->GetRenderCamera()->GetProjectionMode() == CameraProjectionMode::CAMERA_PROJECTION_PERSPECTIVE){
		return glm::perspective(glm::radians(60.0f), (float)this->GetWindow()->GetWidth() / (float)this->GetWindow()->GetHeight(), this->GetRenderCamera()->_near, this->GetRenderCamera()->_far);
	}
	else{ // WIP: CAMERA_PROJECTION_ORTHO
		SB_NOT_IMPL;
	}
	return mat4(1.0f);
}

void Renderer::Setup()
{
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// glEnable(GL_STENCIL_TEST);
	// glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	// glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	// glStencilMask(0xFF);
}

void Renderer::Loop()
{
    glfwPollEvents();
	
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.52f, 0.36f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glStencilOp()

    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);

}
