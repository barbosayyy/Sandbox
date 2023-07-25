#include "window.h"

void Window::installMainCallbacks()
{
	if (nativeWindow != nullptr)
	{
		//glfwSetKeyCallback(nativeWindow, Input::keycallback);
	}
}

void Window::close()
{
	if (nativeWindow != nullptr)
	{
		glfwSetWindowShouldClose(nativeWindow, GLFW_TRUE);
	}
}

Window* Window::createWindow(int width, int height, const char* title, bool fullscreenMode)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	Window* resolution = new Window();

	GLFWmonitor* primaryMonitor = fullscreenMode ? glfwGetPrimaryMonitor() : nullptr;
	resolution->nativeWindow = glfwCreateWindow(width, height, title, primaryMonitor, nullptr);
	
	if (resolution->nativeWindow == nullptr)
	{
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(resolution->nativeWindow);
	return resolution;
}

void Window::freeWindow(Window* window)
{
	if (window)
	{
		glfwDestroyWindow(window->nativeWindow);
		delete window;
	}
}