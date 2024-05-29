#pragma once
#include "../Core/Singleton.h"
#include <glew/glew.h>
#include <glfw/glfw3.h>
#include "Window.h"
#include "Camera.h"
#include "../Math/Vectors.h"

namespace Sandbox{
    constexpr byte RENDERER_OPENGL    = 1 << 0;
    constexpr byte RENDERER_VULKAN    = 1 << 1;
    constexpr byte RENDERER_DX12      = 1 << 2;

    constexpr u16 DEFAULT_SCREEN_W    = 2160;
    constexpr u16 DEFAULT_SCREEN_H    = 1440;
}

namespace Sandbox{

    // (Singleton) Sandbox Renderer class 

    class Renderer : Singleton<Renderer, int>{
        private:
            Window* _windowHandle;
            Camera* _renderCamera;
            byte _renMode;

            u16 _screenWidth;
            u16 _screenHeight;

        public:
            Renderer();
            ~Renderer();

            Window* GetWindow() {return _windowHandle;};
            Camera* GetRenderCamera() {return _renderCamera;};
            u16 GetScreenWidth() const {return _screenWidth;};
            u16 GetScreenHeight() const {return _screenHeight;};
            mat4 GetProjection();
            void SetRenderCamera(Camera* camera) {_renderCamera = camera;};
            void Setup();
            void Loop();
    };
}