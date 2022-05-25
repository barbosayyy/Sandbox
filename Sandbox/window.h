#pragma once

#include "core.h"

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