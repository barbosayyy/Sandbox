#include "Window.h"

Window::Window(const char* windowTitle, int windowWidth, int windowHeight)
{
	this->_windowWidth = windowWidth;
	this->_windowHeight = windowHeight;

	Window::createWindow(windowTitle);

	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, FramebufferSizeCallback);
}

void Window::createWindow(const char* windowTitle)
{
	this->_window = glfwCreateWindow(_windowWidth, _windowHeight, "Sandbox", NULL, NULL);
}

//

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window::~Window()
{
	glfwDestroyWindow(_window);
}