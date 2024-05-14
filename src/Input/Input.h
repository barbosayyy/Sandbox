#pragma once

#include "../Core/Singleton.h"
#include "../Core/Base.h"
#include <glfw/glfw3.h>
#include <functional>
#include "../Renderer/Window.h"
#include <imgui/imgui.h>

namespace Sandbox {
	class InputManager : public Singleton<InputManager, GLFWwindow*> {
	public:
		InputManager(GLFWwindow* window);
		InputManager();
		~InputManager();

		void ProcessInput();

		void AddInputFunction(std::function<void()> function);
		void AddMouseAxisMoveFunction(std::function<void(float xOffset, float yOffset)> function);
		void SetCallbacks();
		static int PressedKey(int key);
		static int PressedMouse(int key);

		float xOffset = 0.0f;
		float yOffset = 0.0f;

		GLFWwindow* window;
	private:
		std::vector<std::function<void()>> onInputFunctions;
		std::vector<std::function<void(float xOffset, float yOffset)>> onMouseAxisMoveFunctions;

		bool _firstMouse = true;
		double _mouseX = 0.0;
		double _mouseY = 0.0;
		float _mouseLastFrameX = WINDOW_WIDTH * 0.5;
		float _mouseLastFrameY = WINDOW_HEIGHT * 0.5;

		static void MouseAxisMoveCallback(GLFWwindow* window, double xpos, double ypos);
	};
}