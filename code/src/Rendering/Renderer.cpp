#include "Rendering/Renderer.h"
#include "Core/Base.h"
#include "Core/Debug.h"
#include "Core/Config.h"
#include "Core/Types.h"
#include "ImGui/ImGuiSbContext.h"
#include "Resources/ResourceManager.h"

using namespace Sb;

Renderer::Renderer() : _currentAPI(0x0), _viewportWidth(DEFAULT_VIEWPORT_WIDTH), _viewportHeight(DEFAULT_VIEWPORT_HEIGHT), _viewportX(DEFAULT_VIEWPORT_X), _viewportY(DEFAULT_VIEWPORT_Y) {
	_currentAPI |= SB_OPENGL;

	Log::Info("Renderer: Starting with Mode: ", static_cast<int>(_currentAPI));

	if(_currentAPI & SB_OPENGL) {
		if(!glfwInit()) {
			SB_ASSERT("Renderer: Failed to initialize GLFW.");
		}
		_windowHandle = new Window("SandboxWindow", DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
		if(!_windowHandle->GLWindow()) {
			glfwTerminate();
			SB_ASSERT("Renderer: Failed to create window.");
		}

		glfwSetFramebufferSizeCallback(_windowHandle->GLWindow(), this->GlFramebufferSizeCallback);

		// GLEW initialization
		if(glewInit() != GLEW_OK) {
			glfwTerminate();
			SB_ASSERT("Renderer: Failed to initialize GLEW.");
		} else {
			Log::Info("Renderer: Init OGL");
		}
	} else if(_currentAPI & SB_VULKAN) {
		SB_NOT_IMPL;
	} else if(_currentAPI & SB_DX11) {
		SB_NOT_IMPL;
	} else if(_currentAPI & SB_DX12) {
		SB_NOT_IMPL;
	}

	_imGuiSbContext = new ImGuiSbContext();
}

Renderer::~Renderer() {
	delete _renderCamera;
	delete _windowHandle;
	delete _imGuiSbContext;

	if(_currentAPI & SB_OPENGL)
		glfwTerminate();
}

void Renderer::Setup() {

	_imGuiSbContext->Init(this->_windowHandle, SbImGuiStyle::IMGUI_DARK, this->_currentAPI);

	SetupFramebufferQuad();

	glGenFramebuffers(1, &_gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);

	GenerateFramebufferTextures();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glPolygonMode(GL_FRONT, GL_FILL);
}

void Renderer::OnBeginFrame() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GetImGuiSbContext().NewRendererFrame();
}

void Renderer::GenerateFramebufferTextures(){
	if(gPosition)
		glDeleteTextures(1, &this->gPosition);
	if(gNormal)
		glDeleteTextures(1, &this->gNormal);
	if(gAlbedoSpec)
		glDeleteTextures(1, &this->gAlbedoSpec);

	if(_renderBufferObject) {
		glDeleteRenderbuffers(1, &this->_renderBufferObject);
		_renderBufferObject = 0;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);

	glGenTextures(1, &gPosition);
	glBindTexture(GL_TEXTURE_2D, gPosition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->GetViewportWidth(), this->GetViewportHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

	glGenTextures(1, &gNormal);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->GetViewportWidth(), this->GetViewportHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

	glGenTextures(1, &gAlbedoSpec);
	glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->GetViewportWidth(), this->GetViewportHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);

	u32 attachments[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
	glDrawBuffers(3, attachments);

	// Depth render buffer
	glGenRenderbuffers(1, &_renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, _renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->GetViewportWidth(), this->GetViewportHeight());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _renderBufferObject);
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		Log::Warn("Renderer: Render buffer object incomplete");
	}
}

void Renderer::DrawFramebufferQuad(bool useDefaultQuadShader) {
	if(useDefaultQuadShader) {
		framebufferQuadShader->Use();
	}
	glBindVertexArray(this->framebufferVao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Renderer::GlFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	Renderer& ren = Renderer::GetInstance();
	ren.SetViewportWidth(width);
	ren.SetViewportHeight(height);
	glViewport(ren.GetViewportX(), ren.GetViewportY(), width, height);
	ren.GenerateFramebufferTextures();
	ren._stateDirtyFlags |= SB_DIRTY_PROJECTION;
	Log::Info("Renderer: Framebuffer resize: ", "Width: ", width, " Height: ", height);
}

void Renderer::SetupFramebufferQuad() {
	glGenVertexArrays(1, &this->framebufferVao);
	glGenBuffers(1, &this->framebufferVbo);
	glBindVertexArray(this->framebufferVao);

	glBindBuffer(GL_ARRAY_BUFFER, this->framebufferVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SB_TEX_QUAD), &SB_TEX_QUAD, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	ResourceManagement::ResourceManager& res = ResourceManagement::ResourceManager::GetInstance();
	framebufferQuadShader = res.LoadShader(48, 47);
}