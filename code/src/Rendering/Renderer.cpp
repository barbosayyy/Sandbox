#include "Rendering/Renderer.h"
#include "Core/Base.h"
#include "Core/Debug.h"
#include "Core/Config.h"
#include "Core/Types.h"
#include "ImGui/ImGuiSbContext.h"
#include "OpenGL/GLBuffer.h"
#include "RenderPasses/GeometryPass.h"
#include "RenderPasses/LightingPass.h"
#include "RenderPasses/SkyboxPass.h"
#include "Resources/ResourceManagement.h"
#include "Resources/DefaultPrimitives.h"

#include "glfw/glfw3.h"

namespace Sb {

	void LogRendererInfo(u8 api) {
		if(api & SB_OPENGL) {
			Log::Info("Renderer: OpenGL version ", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
			Log::Info("Device: ", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		}
	}

	Renderer::Renderer() : _currentAPI(0x0), _viewportWidth(DEFAULT_VIEWPORT_WIDTH), _viewportHeight(DEFAULT_VIEWPORT_HEIGHT), _viewportX(DEFAULT_VIEWPORT_X), _viewportY(DEFAULT_VIEWPORT_Y) {

		_currentAPI |= SB_OPENGL;
		
		if(_currentAPI & SB_OPENGL) {
			if(!glfwInit()) {
				SB_ASSERT("Renderer: Failed to initialize GLFW.");
			}

			// GLFW config
			glfwDefaultWindowHints();
			glfwWindowHint(GLFW_RED_BITS, 8);				// Frame bit length
			glfwWindowHint(GLFW_GREEN_BITS, 8);			
			glfwWindowHint(GLFW_BLUE_BITS, 8);				
			glfwWindowHint(GLFW_ALPHA_BITS, 8);			
			glfwWindowHint(GLFW_DEPTH_BITS, 16);			
			glfwWindowHint(GLFW_DOUBLEBUFFER, SB_RENDERER_TRIPLE_BUFFERING);	// Triple buffering		
			glfwWindowHint(GLFW_SAMPLES, 0);				// MSAA
			
			_windowHandle = new Window("SandboxWindow", DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
			glfwSwapInterval(SB_RENDERER_VSYNC);
			
			if(!_windowHandle->GLWindow()) {
				glfwTerminate();
				SB_ASSERT("Renderer: Failed to create window.");
			}
	
			glfwSetFramebufferSizeCallback(_windowHandle->GLWindow(), this->GLFramebufferSizeCallback);
	
	
			// GLEW initialization
			if(glewInit() != GLEW_OK) {
				glfwTerminate();
				SB_ASSERT("Renderer: Failed to initialize GLEW.");
			} else {
				LogRendererInfo(_currentAPI);
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
		
		GLAllocateLightUBO(_glLightData.lightUBO);
	
		AddRenderPass(std::make_unique<GeometryPass>());
		AddRenderPass(std::make_unique<LightingPass>());
		AddRenderPass(std::make_unique<SkyboxPass>());
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
			if(framebufferQuadShader != nullptr)
				framebufferQuadShader->Use();
		}
		glBindVertexArray(this->framebufferVao);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}
	
	void Renderer::GLFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
		Renderer& ren = Renderer::GetInstance();
		ren.SetViewportWidth(width);
		ren.SetViewportHeight(height);
		glViewport(ren.GetViewportX(), ren.GetViewportY(), width, height);
		ren.GenerateFramebufferTextures();
		ren._stateDirtyFlags |= SB_DIRTY_PROJECTION;
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
	
		framebufferQuadShader = ResourceManagement::LoadShader("common/shaders/ScreenQuad.vert", "common/shaders/ScreenQuad.frag");
	}
}
