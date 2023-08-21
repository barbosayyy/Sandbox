#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <windows.h>
#include <memory>

#include <GL/glew.h>
#include <glfw3.h>
#include <glm.hpp>

#include "shaders.h"
#include "input.h"
#include "primitives.h"

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600
const char* windowTitle = "Sandbox";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (glewInit() != GLEW_OK)
	{
		return -1;
	}

	//

	Square* square = new Square(0.0, 1.0);

	Texture *texture1 = new Texture("assets/container.jpg", JPG, GL_REPEAT);
	Texture *texture2 = new Texture("assets/test.png", PNG, GL_REPEAT);

	square->texture.push_back(texture1->texture);
	square->texture.push_back(texture2->texture);

	Shader yellow("src/shaders/vertex.vert", "src/shaders/yellow.frag");
	Shader texShader("src/shaders/tex.vert", "src/shaders/tex.frag");
	
	texShader.use();
	texShader.setInt("texture1", 0);
	texShader.setInt("texture2", 1);
	texShader.setFloat("mixValue", 0.0);

	std::cout << a.x << a.y << a.z << std::endl;
	while (!glfwWindowShouldClose(window))
	{
		Input::processInput(window);

		glClearColor(0.15f, 0.18f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		square->draw();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}