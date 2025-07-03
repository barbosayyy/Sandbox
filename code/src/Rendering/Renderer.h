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

namespace SbEngine{
    class Renderer : public Singleton<Renderer, int>{
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
        
        u8 GetRendererMode() const {return _apiMode;};
        Window* GetWindow() {return _windowHandle;};
        Camera* GetRenderCamera() {return _renderCamera;};
        u16 GetScreenWidth() const {return _screenWidth;};
        u16 GetScreenHeight() const {return _screenHeight;};
        mat4 GetProjection();
        ImGuiSbContext& GetImGuiSbContext() const {return *_imGuiSbContext;};
        
        void SetRenderCamera(Camera* camera) {_renderCamera = camera;};
        // Functionality is dependent on specific shaders that support screen texture
        void DrawFramebufferQuad();

        void Init();
        void Setup();
        void OnBeginFrame();
    private:
        u16 _screenWidth;
        u16 _screenHeight;
        u8 _apiMode;
        u32 framebufferVao, framebufferVbo;
        Shader* framebufferQuadShader;

        Window* _windowHandle;
        Camera* _renderCamera;
        ImGuiSbContext* _imGuiSbContext;
        
        void SetupFramebufferQuad();
    };
}