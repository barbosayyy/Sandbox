#include "Renderer.h"
#include "../Core/Debug.h"

using namespace Sandbox;

Renderer::Renderer() : rMode(0x0){
	if(_instance == nullptr){
		_instance = this;
		
		rMode |= RENDERER_OPENGL;
		if(rMode & RENDERER_OPENGL){
			if (!glfwInit())
			{
				assert("Failed to initialize GLFW.");
			}
			_windowHandle = new Window("Sandbox", WINDOW_WIDTH, WINDOW_HEIGHT);
			if (!_windowHandle->GLWindow())
			{
				glfwTerminate();
				assert("Failed to find window.");
			}
			// GLEW initialization
			if (glewInit() != GLEW_OK)
			{
				glfwTerminate();
				assert("Failed to initialize GLEW.");
			}
			Logger::Trace(LogLevel::RUNTIME, "Started Sandbox Renderer, Mode: ", static_cast<int>(rMode));
		}
		else if(rMode & RENDERER_VULKAN){
			assert("Vulkan isn't ready yet!");
		}
		else if(rMode & RENDERER_DX12){
			assert("DirectX isn't ready yet!");
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
		assert("Not implemented yet");
	}
	return mat4(1.0f);
}

void Renderer::Setup()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glStencilMask(0xFF);
}

void Renderer::Loop()
{
    glfwPollEvents();
	glClearColor(0.52f, 0.36f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glStencilOp()

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}
