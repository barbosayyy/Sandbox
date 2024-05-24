#pragma once
#include "../Core/Singleton.h"
#include <glew/glew.h>
#include <glfw/glfw3.h>
#include "Window.h"
#include "Camera.h"
#include "../Math/Vectors.h"

namespace Sandbox{
    constexpr byte RENDERER_OPENGL    = 0x1;
    constexpr byte RENDERER_VULKAN    = 0x2;
    constexpr byte RENDERER_DX12      = 0x3;
}

namespace Sandbox{

    class Renderer : Singleton<Renderer, int>{
        private:
            Window* _windowHandle;
            Camera* _renderCamera;
            byte rMode;
        public:
            Renderer();
            ~Renderer();

            Window* GetWindow() {return _windowHandle;};
            Camera* GetRenderCamera() {return _renderCamera;};
            mat4 GetProjection();
            void SetRenderCamera(Camera* camera) {_renderCamera = camera;};
            void Setup();
            void Loop();
    };
}