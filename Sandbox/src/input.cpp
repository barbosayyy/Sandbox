#include "input.h"

namespace Input {
	void processInput(GLFWwindow* window)
	{
		// Close window
		if (pressedKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
	}

	int pressedKey(GLFWwindow* window, int key)
	{
		return glfwGetKey(window, key);
	}
}
