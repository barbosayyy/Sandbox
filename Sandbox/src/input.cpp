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
		}
	}

	InputListener::~InputListener()
	{
	}

	void InputListener::addInputFunction(std::function<void()> inputFunction)
	{
		inputFunctions.push_back(inputFunction);
	}

	void InputListener::processInput(GLFWwindow* window)
	{
		for (const auto& func : inputFunctions)
		{
			func();
		}
	}

	int InputListener::pressedKey(int key)
	{
		return glfwGetKey(this->window, key);
	}


}
