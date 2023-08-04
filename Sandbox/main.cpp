#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <windows.h>

#include <GL/glew.h>
#include <glfw3.h>

#include "shaders.h"
#include "input.h"
#include "primitives.h"

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600
const char* windowTitle = "Sandbox";

const char* vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec3 aPosition;

    void main()	
    {
        gl_Position = vec4(aPosition.x, aPosition.y, aPosition.z, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core    
    out vec4 fragColor;

    void main()
    {
        fragColor = vec4(1.0, 0.5, 0.2, 1.0);
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

	//

	Triangle* triangle = new Triangle();

	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	ShaderProgram shaderProgram;

	shaderProgram.attachShader(shaderProgram.sProgram, vertexShader);
	shaderProgram.attachShader(shaderProgram.sProgram, fragmentShader);
	shaderProgram.loadProgram(shaderProgram.sProgram);

	deleteShader(vertexShader);
	deleteShader(fragmentShader);

	//

	while (!glfwWindowShouldClose(window))
	{
		Input::processInput(window);

		glClearColor(0.15f, 0.18f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		triangle->draw();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}