#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

#include <glfw3.h>
#include <GL/glew.h>

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

unsigned int compileShaders(GLenum shaderType, const char* shaderSource)
{
	auto shader = glCreateShader(shaderType);

	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	int successful;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &successful);
	if (successful == false)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "Shader compilation error:\n" << infoLog << std::endl;
		glDeleteShader(shader);
		return 0;
	}
}

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

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}