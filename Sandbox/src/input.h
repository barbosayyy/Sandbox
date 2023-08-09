#pragma once

#include <glfw3.h>

namespace Input {
	void processInput(GLFWwindow* window);

	int pressedKey(GLFWwindow* window, int key);
}