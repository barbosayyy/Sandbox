#pragma once

#include <glfw3.h>

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600

struct Window
{
	GLFWwindow* nativeWindow;
	int windowWidth;
	int windowHeight;
	static bool fullscreenMode;

	void installMainCallbacks();

	void close();

	static Window* createWindow(int width, int height, const char* title, bool fullscreenMode = false);
	static void freeWindow(Window* window);
};