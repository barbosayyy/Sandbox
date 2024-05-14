#pragma once

#include <glfw/glfw3.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class Window {
public:
	Window(const char* windowTitle, int windowWidth, int windowHeight);
	~Window();
	
	GLFWwindow* GLWindow();
	int GetWidth();
	int GetHeight();
	void SetWidth();
	void SetHeight();

	operator GLFWwindow* const() {
		return _window;
	}
private:
	int _windowWidth;
	int _windowHeight;
	GLFWwindow* _window;
	void createWindow(const char* windowTitle);
};

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);