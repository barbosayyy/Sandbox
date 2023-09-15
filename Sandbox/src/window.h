#pragma once

#include <glfw/glfw3.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

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