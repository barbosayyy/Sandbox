#include "input.h"
#include "core.h"

namespace Input
{
	bool keyPressedData[GLFW_KEY_LAST] = {};

	void keycallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key >= 0 && key < GLFW_KEY_LAST)
		{
			keyPressedData[key] = action == GLFW_PRESS;
		}
	}

	bool isKeyDown(int key)
	{
		if (key >= 0 && key < GLFW_KEY_LAST)
		{
			return keyPressedData[key];
		}

		return false;
	}
}


