#include "Input/Input.h"
#include "Core/Debug.h"
#include "glfw/glfw3.h"

using namespace Sb;

InputManager::InputManager()
{
}

InputManager::InputManager(GLFWwindow* window) : _window(window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	pressedQueue.reserve(SB_KEYBOARD_MENU);
}

InputManager::~InputManager()
{
}

void InputManager::SetCallbacks()
{
	glfwSetCursorPosCallback(_window, MouseAxisMoveCallback);
}

void InputManager::MouseAxisMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	InputManager::GetInstance()._mouseX = xpos;
	InputManager::GetInstance()._mouseY = ypos;

	if (InputManager::GetInstance()._firstMouse)
	{
		InputManager::GetInstance()._mouseLastFrameX = InputManager::GetInstance()._mouseX;
		InputManager::GetInstance()._mouseLastFrameY = InputManager::GetInstance()._mouseY;
		InputManager::GetInstance()._firstMouse = false;
	}
	InputManager::GetInstance().xOffset = InputManager::GetInstance()._mouseX - InputManager::GetInstance()._mouseLastFrameX;
	InputManager::GetInstance().yOffset = InputManager::GetInstance()._mouseLastFrameY - InputManager::GetInstance()._mouseY;
	InputManager::GetInstance()._mouseLastFrameX = InputManager::GetInstance()._mouseX;
	InputManager::GetInstance()._mouseLastFrameY = InputManager::GetInstance()._mouseY;
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
	if(pressedQueue.size() > 0) {
		for(u16 i = 0; i < pressedQueue.size();) {
			if(glfwGetKey(_window, pressedQueue[i]) == GLFW_RELEASE) {
				keyState[pressedQueue[i]] = 2;
				if(pressedQueue.size() > 1) {
					pressedQueue[i] = pressedQueue.back();
					pressedQueue.pop_back();
					continue;
				}
				else {
					pressedQueue.pop_back();
				}
			}
			i++;
		}
	}
	for (const auto& func : onInputFunctions)
	{
		func();
	}
	if (InputManager::GetInstance()._mouseLastFrameX != ImGui::GetMousePos().x || InputManager::GetInstance()._mouseLastFrameY != ImGui::GetMousePos().y)
	{
		MouseAxisMoveCallback(_window, ImGui::GetMousePos().x, ImGui::GetMousePos().y);
		for (const auto& func : InputManager::GetInstance().onMouseAxisMoveFunctions)
		{
			func(InputManager::GetInstance().xOffset, InputManager::GetInstance().yOffset);
		}
	}
}

bool InputManager::PressedKey(int key) {
	InputManager& inp = InputManager::GetInstance();
	if(glfwGetKey(inp._window, key) == GLFW_PRESS){
		if(inp.keyState[key] == 0 || inp.keyState[key] == 2) {
			inp.keyState[key] = 1;
			inp.pressedQueue.push_back(key);
			return true;
		}
	}
	return false;
}

bool InputManager::PressingKey(int key) {
	InputManager& inp = InputManager::GetInstance();
	if(glfwGetKey(inp._window, key) == GLFW_PRESS){
		if(inp.keyState[key] == 0 || inp.keyState[key] == 2) {
			inp.keyState[key] = 1;
			inp.pressedQueue.push_back(key);
		}
		return true;
	}
	return false;
}

// TODO This input system needs a rework

// bool InputManager::ReleasedKey(int key) {
// 	InputManager& inp = InputManager::GetInstance();

// 	return false;
// }

int InputManager::PressedMouse(int key)
{
	int state = glfwGetMouseButton(InputManager::GetInstance()._window, key);
	if (state == SB_PRESS)
	{
		glfwSetInputMode(InputManager::GetInstance()._window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		return SB_PRESS;
	}
	else if (state == SB_RELEASE)
	{
		glfwSetInputMode(InputManager::GetInstance()._window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		return SB_RELEASE;
	}
	return -1;
}