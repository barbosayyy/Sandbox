#include "input.h"

namespace Input {
	InputListener* InputListener::instance = NULL;

	InputListener* InputListener::getInstance()
	{
		if (instance == NULL)
		{
			std::cout << "Instance not created" << std::endl;
		}
		return instance;
	}

	InputListener::InputListener()
	{

	}

	InputListener::InputListener(GLFWwindow* window) : window(window)
	{
		if (!instance)
		{
			instance = this;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			setCallbacks();
		}
	}

	InputListener::~InputListener()
	{
	}

	void InputListener::setCallbacks()
	{
		glfwSetCursorPosCallback(window, mouseAxisMoveCallback);
	}

	void InputListener::mouseAxisMoveCallback(GLFWwindow* window, double xpos, double ypos)
	{
		instance->mouseX = xpos;
		instance->mouseY = ypos;

		if (instance->firstMouse)
		{
			instance->mouseLastFrameX = instance->mouseX;
			instance->mouseLastFrameY = instance->mouseY;
			instance->firstMouse = false;
		}
		instance->xOffset = instance->mouseX - instance->mouseLastFrameX;
		instance->yOffset = instance->mouseLastFrameY - instance->mouseY;
		instance->mouseLastFrameX = instance->mouseX;
		instance->mouseLastFrameY = instance->mouseY;

		for (const auto& func : instance->onMouseAxisMoveFunctions)
		{
			func(instance->xOffset, instance->yOffset);
		}
	}

	void InputListener::addInputFunction(std::function<void()> function)
	{
		onInputFunctions.push_back(function);
	}

	void InputListener::addMouseAxisMoveFunction(std::function<void(float xOffset, float yOffset)> function)
	{
		onMouseAxisMoveFunctions.push_back(function);
	}

	void InputListener::processInput()
	{
		for (const auto& func : onInputFunctions)
		{
			func();
		}
	}

	//

	int Input::pressedKey(int key)
	{
		return glfwGetKey(Input::InputListener::getInstance()->window, key);
	}

	int Input::pressedMouse(int key)
	{
		int state = glfwGetMouseButton(Input::InputListener::getInstance()->window, key);
		if (state == GLFW_PRESS)
		{
			glfwSetInputMode(Input::InputListener::getInstance()->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			return GLFW_PRESS;
		}
		else if (state == GLFW_RELEASE)
		{
			glfwSetInputMode(Input::InputListener::getInstance()->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			return GLFW_RELEASE;
		}
	}
}
