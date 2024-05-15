#include "Input.h"

using namespace Sandbox;

InputManager::InputManager()
{
}

InputManager::InputManager(GLFWwindow* window) : window(window)
{
	if(_instance == nullptr)
	{
		_instance = this;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

InputManager::~InputManager()
{
}

void InputManager::SetCallbacks()
{
	glfwSetCursorPosCallback(window, MouseAxisMoveCallback);
}

void InputManager::MouseAxisMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	InputManager::GetInstance()->_mouseX = xpos;
	InputManager::GetInstance()->_mouseY = ypos;

	if (InputManager::GetInstance()->_firstMouse)
	{
		InputManager::GetInstance()->_mouseLastFrameX = InputManager::GetInstance()->_mouseX;
		InputManager::GetInstance()->_mouseLastFrameY = InputManager::GetInstance()->_mouseY;
		InputManager::GetInstance()->_firstMouse = false;
	}
	InputManager::GetInstance()->xOffset = InputManager::GetInstance()->_mouseX - InputManager::GetInstance()->_mouseLastFrameX;
	InputManager::GetInstance()->yOffset = InputManager::GetInstance()->_mouseLastFrameY - InputManager::GetInstance()->_mouseY;
	InputManager::GetInstance()->_mouseLastFrameX = InputManager::GetInstance()->_mouseX;
	InputManager::GetInstance()->_mouseLastFrameY = InputManager::GetInstance()->_mouseY;
}

void InputManager::AddInputFunction(std::function<void()> function)
{
	onInputFunctions.push_back(function);
}

void InputManager::AddMouseAxisMoveFunction(std::function<void(float xOffset, float yOffset)> function)
{
	onMouseAxisMoveFunctions.push_back(function);
}

void InputManager::ProcessInput()
{
	for (const auto& func : onInputFunctions)
	{
		func();
	}
	if (InputManager::GetInstance()->_mouseLastFrameX != ImGui::GetMousePos().x || InputManager::GetInstance()->_mouseLastFrameY != ImGui::GetMousePos().y)
	{
		MouseAxisMoveCallback(InputManager::GetInstance()->window, ImGui::GetMousePos().x, ImGui::GetMousePos().y);
		for (const auto& func : InputManager::GetInstance()->onMouseAxisMoveFunctions)
		{
			func(InputManager::GetInstance()->xOffset, InputManager::GetInstance()->yOffset);
		}
	}
}

int InputManager::PressedKey(int key)
{
	return glfwGetKey(InputManager::GetInstance()->window, key);
}

int InputManager::PressedMouse(int key)
{
	int state = glfwGetMouseButton(InputManager::GetInstance()->window, key);
	if (state == SB_PRESS)
	{
		glfwSetInputMode(InputManager::GetInstance()->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		return SB_PRESS;
	}
	else if (state == SB_RELEASE)
	{
		glfwSetInputMode(InputManager::GetInstance()->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		return SB_RELEASE;
	}
	return -1;
}