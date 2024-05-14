#include "Renderer.h"
#include "../Core/Debug.h"

using namespace Sandbox;

Renderer::Renderer(){
    // GLFW initialization
		if (!glfwInit())
		{
			Logger::Trace(LogLevel::CRITICAL, "Failed to initialize GLFW. Exiting");
			// return -1;
		}
		_windowHandle = new Window("Sandbox", WINDOW_WIDTH, WINDOW_HEIGHT);
		if (!_windowHandle->GLWindow())
		{
			Logger::Trace(LogLevel::CRITICAL, "Failed to find window. Exiting");
			glfwTerminate();
			// return -1;
		}
		// GLEW initialization
		if (glewInit() != GLEW_OK)
		{
			Logger::Trace(LogLevel::CRITICAL, "Failed to initialize GLEW. Exiting");
			// return -1;
		}
}

Renderer::~Renderer()
{
    delete _windowHandle;
}

Window* Renderer::GetWindow()
{
    return _windowHandle;
}

void Renderer::Loop()
{
    glfwPollEvents();
		
    glClearColor(0.32f, 0.58f, 0.45f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glEnable(GL_DEPTH_TEST);

    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
}
