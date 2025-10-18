#pragma once

#include "Core/Base.h"
#include "Core/Singleton.h"
#include <glew/glew.h>
#include <glfw/glfw3.h>
#include "Light.h"
#include "Rendering/Camera.h"
#include "Rendering/Window.h"
#include "Rendering/Texture.h"
#include "ImGui/ImGuiSbContext.h"
#include "RenderPasses/RenderPass.h"
#include "Shader.h"

namespace Sb {
	class Renderer : public Singleton<Renderer, int> {
	public:
		Renderer();
		~Renderer();

		void Init();
		void Setup();
		void OnBeginFrame();
		void GenerateFramebufferTextures();

		// Renderer Get/Set	
			u8 GetRendererMode() const { return _currentAPI; };
			Camera* GetRenderCamera() { return _renderCamera; };
			void SetRenderCamera(Camera* camera) { _renderCamera = camera; };
			Window* GetWindow() { return _windowHandle; };
			ImGuiSbContext& GetImGuiSbContext() const { return *_imGuiSbContext; };
			int GetViewportWidth() const { return _viewportWidth; };
			int GetViewportHeight() const { return _viewportHeight; };
			int GetViewportX() const { return _viewportX; };
			int GetViewportY() const { return _viewportY; };
			void SetViewportWidth(int width) { _viewportWidth = width; };
			void SetViewportHeight(int height) { _viewportHeight = height; };
			void SetViewportX(int x) { _viewportX = x; };
			void SetViewportY(int y) { _viewportY = y; };
			u8 GetStateDirtyFlags() const { return _stateDirtyFlags; };
			std::vector<std::unique_ptr<RenderPass>>& GetRenderpasses() { return renderingPasses; };

		// Depends on screen texture shaders. Use Default screen quad shader only when debugging framebuffers
		void DrawFramebufferQuad(bool useDefaultQuadShader);
		static void GlFramebufferSizeCallback(GLFWwindow* window, int width, int height);
		void ClearStateDirtyFlags(u8 mask) { _stateDirtyFlags &= ~mask; };

		u8 _stateShowBufferMask {0};
		u32 _faceAmount {0};

		// Framebuffer data
			u32 _gBuffer;
			u32 gPosition, gNormal, gAlbedoSpec;
			u32 _renderBufferObject;
			u32 _fbo;
			u32 _lightUBO;
			LightUBOData _lightUBOData;

	private:
		void SetupFramebufferQuad();
		void AddRenderPass(std::unique_ptr<RenderPass> pass) { renderingPasses.push_back(std::move(pass)); };

		u8 _currentAPI;
		u16 _viewportWidth;
		u16 _viewportHeight;
		u16 _viewportX;
		u16 _viewportY;
		Camera* _renderCamera;
		Window* _windowHandle;
		ImGuiSbContext* _imGuiSbContext;
		u32 framebufferVao, framebufferVbo;
		Shader* framebufferQuadShader;
		u8 _stateDirtyFlags;
		std::vector<std::unique_ptr<RenderPass>> renderingPasses;
	};
}