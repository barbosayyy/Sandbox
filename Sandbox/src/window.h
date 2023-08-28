#pragma once

#include <glfw3.h>

class Window {
public:
	Window(const char* windowTitle, int windowWidth, int windowHeight);
	~Window();
	GLFWwindow* window;
	int getWidth();
	int getHeight();
private:
	int windowWidth;
	int windowHeight;
	void createWindow(const char* windowTitle);
};

void framebufferSizeCallback(GLFWwindow* window, int width, int height);