#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <glfw3.h>

#include <windows.h>
#include "bo_utils.h"
#include "shaders.h"
#include "input.h"

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600
const char* windowTitle = "Sandbox";

const char* vertexShaderSource = R"(
    #version 300 core
    layout(location = 0) in vec3 aPosition

    void main()
    {
        aPosition = vec4(aPosition, 1.0)
    }
)";

const char* fragmentShaderSource = R"(
    #version 300 core    
    out vec4 fragColor;

    void main()
    {
        fragColor = vec4(1.0, 0.5, 0.2, 1.0)
    }
)";

int main(void)
{
	if (!glfwInit())
	{
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, windowTitle, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		return -1;
	}

	//Bind buffer objects here

	while (!glfwWindowShouldClose(window))
	{
		Input::processInput(window);

		glClearColor(0.15f, 0.18f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}