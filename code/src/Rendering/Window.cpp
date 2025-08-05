#include "Core/Debug.h"
#include "Rendering/Renderer.h"
#include "glfw/glfw3.h"
#include "Rendering/Window.h"

namespace Sb {

	void Window::GlWindowSizeCallback(GLFWwindow* window, int width, int height) {
		Renderer& ren = Renderer::GetInstance();
		Log::Print(ren.GetWindow()->GLWindow());
		ren.GetWindow()->SetWindowWidth(width);
		ren.GetWindow()->SetWindowHeight(height);

		if(ren.GetViewportWidth() != width || ren.GetViewportHeight() != height) {
			ren.SetViewportWidth(width);
			ren.SetViewportHeight(height);
			glViewport(ren.GetViewportX(), ren.GetViewportY(), width, height);
		}

		Log::Info("Renderer: Window resize: ", "Width: ", width, " Height: ", height);
	}

	Window::Window(const char* windowTitle, int width, int height)
	{
		this->_windowWidth = width;
		this->_windowHeight = height;

		Window::CreateWindow(windowTitle);
		Log::Print(_window);
		glfwMakeContextCurrent(_window);
		glfwSetWindowSizeCallback(_window, this->GlWindowSizeCallback);
	}

	void Window::CreateWindow(const char* windowTitle)
	{
		this->_window = glfwCreateWindow(_windowWidth, _windowHeight, "Sandbox", nullptr, nullptr);
	}

	//

	Window::~Window()
	{
		glfwDestroyWindow(_window);
	}
}