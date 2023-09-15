#pragma once

#include <iostream>
#include <glfw/glfw3.h>
#include <functional>
#include "window.h"

namespace Input {

	class InputListener {
	public:
		static InputListener* getInstance();

		InputListener();
		InputListener(GLFWwindow* window);
		~InputListener();

		void processInput();

		void addInputFunction(std::function<void()> function);
		void addMouseAxisMoveFunction(std::function<void(float xOffset, float yOffset)> function);

		float xOffset = 0.0f;
		float yOffset = 0.0f;

		GLFWwindow* window;
	private:
		static InputListener* instance;
		InputListener(const InputListener&) = delete;
		
		std::vector<std::function<void()>> onInputFunctions;
		std::vector<std::function<void(float xOffset, float yOffset)>> onMouseAxisMoveFunctions;

		bool firstMouse = true;
		double mouseX = 0.0;
		double mouseY = 0.0;
		float mouseLastFrameX = WINDOW_WIDTH * 0.5;
		float mouseLastFrameY = WINDOW_HEIGHT * 0.5;

		void setCallbacks();
		static void mouseAxisMoveCallback(GLFWwindow* window, double xpos, double ypos);
	};

	int pressedKey(int key);
	int pressedMouse(int key);
}

