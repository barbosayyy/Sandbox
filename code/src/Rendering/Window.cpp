#include "Core/Debug.h"
#include "Rendering/Renderer.h"
#include "Rendering/Window.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3.h"
#include <GLFW/glfw3native.h>

#ifdef SB_PLATFORM_WIN
#include "dwmapi.h"
#endif

namespace Sb {

	void Window::GlWindowSizeCallback(GLFWwindow* window, int width, int height) {
		Renderer& ren = Renderer::GetInstance();
		ren.GetWindow()->SetWindowWidth(width);
		ren.GetWindow()->SetWindowHeight(height);
		
		if((ren.GetViewportWidth() != width || ren.GetViewportHeight() != height) && (ren.GetViewportWidth() > 0 || ren.GetViewportHeight() > 0)) {
			ren.SetViewportWidth(width);
			ren.SetViewportHeight(height);
			glViewport(ren.GetViewportX(), ren.GetViewportY(), width, height);
			Log::Info("Renderer: Window resize: ", "Width: ", width, " Height: ", height);
		}
	}

	void Window::SetWindowTitle(String windowTitle) {
		glfwSetWindowTitle(this->_window, windowTitle.c_str());
	}

	Window::Window(const char* windowTitle, int width, int height)
	{
		this->_windowWidth = width;
		this->_windowHeight = height;

		Window::CreateWindowasdf(windowTitle);
		glfwMakeContextCurrent(_window);
		glfwSetWindowSizeCallback(_window, this->GlWindowSizeCallback);
	}

	void Window::CreateWindowasdf(const char* windowTitle)
	{
		this->_window = glfwCreateWindow(_windowWidth, _windowHeight, windowTitle, nullptr, nullptr);
#ifdef SB_PLATFORM_WIN
		BOOL darkMode = true;
		HWND win = glfwGetWin32Window(this->_window);
		DwmSetWindowAttribute(win, 20, &darkMode, sizeof(darkMode));
#endif
	}

	Window::~Window()
	{
		glfwDestroyWindow(_window);
	}
}