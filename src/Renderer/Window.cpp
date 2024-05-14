#include "Window.h"

Window::Window(const char* windowTitle, int windowWidth, int windowHeight)
{
	this->_windowWidth = windowWidth;
	this->_windowHeight = windowHeight;

	Window::createWindow(windowTitle);

	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, FramebufferSizeCallback);
}

Window::~Window()
{

}

GLFWwindow* Window::GLWindow()
{
	return _window;
}

void Window::createWindow(const char* windowTitle)
{
	this->_window = glfwCreateWindow(_windowWidth, _windowHeight, "Sandbox", NULL, NULL);
}

int Window::GetHeight()
{
	return this->_windowHeight;
}

int Window::GetWidth()
{
	return this->_windowWidth;
}

//

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}