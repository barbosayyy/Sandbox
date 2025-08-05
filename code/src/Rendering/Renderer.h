#pragma once

#include "Core/Base.h"
#include "Core/Singleton.h"
#include <glew/glew.h>
#include <glfw/glfw3.h>
#include "Math/Vectors.h"
#include "Rendering/Camera.h"
#include "Rendering/Window.h"
#include "Rendering/Texture.h"
#include "ImGui/ImGuiSbContext.h"
#include "Resources/ShaderManager.h"

namespace Sb {
	class Renderer : public Singleton<Renderer, int> {
	public:
		std::vector<Texture> _textures;
		ShaderManager _shaderManager;
		u32 _fbo;
		u32 _gBuffer;
		u32 _renderBufferObject;
		u32 gPosition, gNormal, gAlbedoSpec;

		u8 renderMode {1};
		u32 _faceAmount {0};

		Renderer();
		~Renderer();

		u8 GetRendererMode() const { return _apiMode; };
		Window* GetWindow() { return _windowHandle; };
		Camera* GetRenderCamera() { return _renderCamera; };
		int GetViewportWidth() const { return _viewportWidth; };
		int GetViewportHeight() const { return _viewportHeight; };
		int GetViewportX() const { return _viewportX; };
		int GetViewportY() const { return _viewportY; };
		void SetViewportWidth(int width) { _viewportWidth = width; };
		void SetViewportHeight(int height) { _viewportHeight = height; };
		void SetViewportX(int x) { _viewportX = x; };
		void SetViewportY(int y) { _viewportY = y; };

		mat4 GetProjection();
		ImGuiSbContext& GetImGuiSbContext() const { return *_imGuiSbContext; };

		void SetRenderCamera(Camera* camera) { _renderCamera = camera; };
		// Functionality is dependent on specific shaders that support screen texture
		void DrawFramebufferQuad();

		static void GlFramebufferSizeCallback(GLFWwindow* window, int width, int height);

		void Init();
		void Setup();
		void OnBeginFrame();

	private:
		u8 _apiMode;
		u16 _viewportWidth;
		u16 _viewportHeight;
		u16 _viewportX;
		u16 _viewportY;
		u32 framebufferVao, framebufferVbo;
		Shader* framebufferQuadShader;

		Window* _windowHandle;
		Camera* _renderCamera;
		ImGuiSbContext* _imGuiSbContext;

		void SetupFramebufferQuad();
	};
}