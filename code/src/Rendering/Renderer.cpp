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

void Renderer::DrawFramebufferQuad(){
	glBindVertexArray(this->framebufferVao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Renderer::Setup(){
	_imGuiSbContext->Init(this->_windowHandle, SbImGuiStyle::IMGUI_DARK,this->_apiMode);
	
	SetupFramebufferQuad();
	
	glGenFramebuffers(1, &_gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);
	
	glGenTextures(1, &gPosition);
	glBindTexture(GL_TEXTURE_2D, gPosition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->GetWindow()->GetWidth(), this->GetWindow()->GetHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
	
	glGenTextures(1, &gNormal);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->GetWindow()->GetWidth(), this->GetWindow()->GetHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

	glGenTextures(1, &gAlbedoSpec);
	glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->GetWindow()->GetWidth(), this->GetWindow()->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);
	
	u32 attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
	glDrawBuffers(3, attachments);
	
	// RBO Depth
	glGenRenderbuffers(1, &_renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, _renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->GetWindow()->GetWidth(), this->GetWindow()->GetHeight());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _renderBufferObject);
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		Logger::Print("Buffer incomplete");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glPolygonMode(GL_FRONT, GL_FILL);
}

void Renderer::OnBeginFrame(){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GetImGuiSbContext().NewRendererFrame();
}

void Renderer::SetupFramebufferQuad(){
	glGenVertexArrays(1, &this->framebufferVao);
	glGenBuffers(1, &this->framebufferVbo);
	glBindVertexArray(this->framebufferVao);

	glBindBuffer(GL_ARRAY_BUFFER, this->framebufferVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SB_TEX_QUAD), &SB_TEX_QUAD, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	framebufferQuadShader = this->_shaderManager.GetShader(7, 9);
}
