#include "Core/Debug.h"
#include "Rendering/Renderer.h"
#include "glfw/glfw3.h"
#include "Rendering/Window.h"

namespace Sb {

	void Window::GlWindowSizeCallback(GLFWwindow* window, int width, int height) {
		Renderer& ren = Renderer::GetInstance();
		ren.GetWindow()->SetWindowWidth(width);
		ren.GetWindow()->SetWindowHeight(height);

		if((ren.GetViewportWidth() != width || ren.GetViewportHeight() != height) && (ren.GetViewportWidth() > 0 || ren.GetViewportHeight() > 0)) {
			ren.SetViewportWidth(width);
			ren.SetViewportHeight(height);
			glViewport(ren.GetViewportX(), ren.GetViewportY(), width, height);
		}

		Log::Info("Renderer: Window resize: ", "Width: ", width, " Height: ", height);
	}

	void Window::SetWindowTitle(String windowTitle) {
		glfwSetWindowTitle(this->_window, windowTitle.c_str());
	}

	Window::Window(const char* windowTitle, int width, int height)
	{
		this->_windowWidth = width;
		this->_windowHeight = height;

		Window::CreateWindow(windowTitle);
		glfwMakeContextCurrent(_window);
		glfwSetWindowSizeCallback(_window, this->GlWindowSizeCallback);
	}

	void Window::CreateWindow(const char* windowTitle)
	{
		this->_window = glfwCreateWindow(_windowWidth, _windowHeight, windowTitle, nullptr, nullptr);
	}

	//

	Window::~Window()
	{
		glfwDestroyWindow(_window);
	}
}