#pragma once

#include <glfw/glfw3.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

class Window {
public:
	Window(const char* windowTitle, int windowWidth, int windowHeight);
	~Window();
	
	GLFWwindow* GLWindow() {return _window;};
	int GetWidth() const {return _windowWidth;};
	int GetHeight() const {return _windowHeight;};
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