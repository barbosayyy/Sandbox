#pragma once

#include <iostream>
#include <glfw3.h>
#include <functional>

namespace Input {

	class InputListener {
	public:
		static InputListener* getInstance();

		InputListener();
		InputListener(GLFWwindow* window);
		~InputListener();

		void processInput(GLFWwindow* window);
		int pressedKey(int key);

		void addInputFunction(std::function<void()> inputFunction);
	private:
		static InputListener* instance;
		std::vector<std::function<void()>> inputFunctions;
		GLFWwindow* window;

		InputListener(const InputListener&) = delete;
	};
}

