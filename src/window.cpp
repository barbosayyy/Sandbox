#include "window.h"

Window::Window(const char* windowTitle, int windowWidth, int windowHeight)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	Window::createWindow(windowTitle);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}

Window::~Window()
{

}

void Window::createWindow(const char* windowTitle)
{
	this->window = glfwCreateWindow(windowWidth, windowHeight, "Sandbox", NULL, NULL);
}

int Window::getHeight()
{
	return this->windowHeight;
}

int Window::getWidth()
{
	return this->windowWidth;
}

//

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}