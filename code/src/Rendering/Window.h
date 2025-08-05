#pragma once

#include <glfw/glfw3.h>

namespace Sb {

	// Render API window wrapper class
	class Window {
	public:
		Window(const char* windowTitle, int width, int height);
		~Window();

		GLFWwindow* GLWindow() { return _window; };
		int GetWindowWidth() const { return _windowWidth; };
		int GetWindowHeight() const { return _windowHeight; };
		void SetWindowWidth(int width) { _windowWidth = width; };
		void SetWindowHeight(int height) { _windowHeight = height; };

		static void GlWindowSizeCallback(GLFWwindow* window, int width, int height);

		operator GLFWwindow* const() { return _window; }

	private:
		int _windowWidth;
		int _windowHeight;
		GLFWwindow* _window;
		void CreateWindow(const char* windowTitle);
	};
}