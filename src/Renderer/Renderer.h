#pragma once
#include "../Core/Singleton.h"
#include <glew/glew.h>
#include <glfw/glfw3.h>
#include "Window.h"

class Renderer : Singleton<Renderer, int>{
    private:
        Window* _windowHandle;
    public:
        Renderer();
        ~Renderer();

        Window* GetWindow();
        void Loop();
};