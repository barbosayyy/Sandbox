#include "inputevents.h"

namespace InputEvents
{
	void setFullscreen()
	{
		//GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
		if (Input::isKeyDown(GLFW_KEY_0))
		{
			printf("Pressed F12");
		};
	}
}

