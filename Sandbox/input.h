#pragma once

#include "core.h"

namespace Input
{
	extern bool keyPressedData[GLFW_KEY_LAST];

	void keycallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	bool isKeyDown(int key);
}
