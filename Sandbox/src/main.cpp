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

const char* vertex_ShaderSrc = R"(
    #version 330 core
    layout(location = 0) in vec3 aPosition;

    void main()	
    {
        gl_Position = vec4(aPosition.x, aPosition.y, aPosition.z, 1.0);
    }
)";

const char* orangeFrag_ShaderSrc = R"(
    #version 330 core    
    out vec4 fragColor;

	vec4 orangeColor = vec4(1.0, 0.5, 0.2, 1.0);

    void main()
    {
        fragColor = orangeColor;
    }
)";

const char* yellowFrag_ShaderSrc = R"(
    #version 330 core    
    out vec4 fragColor;

	vec4 yellowColor = vec4(1.0, 1.0, 0.0, 1.0);

    void main()
    {
        fragColor = yellowColor;
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

	Square* square = new Square(0.0, 1.0);
	Square* square2 = new Square(1.0, 1.0);

	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertex_ShaderSrc);
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, orangeFrag_ShaderSrc);
	unsigned int fragmentShader2 = compileShader(GL_FRAGMENT_SHADER, yellowFrag_ShaderSrc);

	ShaderProgram shaderProgram;
	ShaderProgram shaderProgram2;

	shaderProgram.attachShader(shaderProgram.sProgram, vertexShader);
	shaderProgram.attachShader(shaderProgram.sProgram, fragmentShader);
	shaderProgram2.attachShader(shaderProgram2.sProgram, vertexShader);
	shaderProgram2.attachShader(shaderProgram2.sProgram, fragmentShader2);

	shaderProgram.loadProgram(shaderProgram.sProgram);
	shaderProgram2.loadProgram(shaderProgram2.sProgram);

	deleteShader(vertexShader);
	deleteShader(fragmentShader);
	deleteShader(fragmentShader2);

	//

	while (!glfwWindowShouldClose(window))
	{
		Input::processInput(window);

		glClearColor(0.15f, 0.18f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shaderProgram.sProgram);
		square->draw();
		
		glUseProgram(shaderProgram2.sProgram);
		square2->draw();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}