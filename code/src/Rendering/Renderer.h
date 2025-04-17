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
            
            void Setup();
            void OnBeginFrame();

            // TODO remove, temp
            std::vector<Texture> _textures;
            ShaderManager _shaderManager;
            u32 _fbo;
            u32 _gBuffer;
        private:
            Window* _windowHandle;
            Camera* _renderCamera;
            ImGuiSbContext* _imGuiSbContext;
            u8 _apiMode;

            u16 _screenWidth;
            u16 _screenHeight;
    };
}