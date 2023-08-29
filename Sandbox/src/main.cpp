#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "window.h"
#include "shaders.h"
#include "input.h"
#include "primitives.h"
#include "camera.h"

void shutdown()
{
	if (Input::InputListener::getInstance()->pressedKey(GLFW_KEY_ESCAPE))
	{
		glfwTerminate();
	}
}

int main(void)
{
	// GLFW initialization
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	Window window("Sandbox", 1920, 1080);

	if (!window.window)
	{
		std::cout << "Failed to find window" << std::endl;
		glfwTerminate;
		return -1;
	}

	// GLEW initialization
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	Input::InputListener inputListener(window.window);
	Input::InputListener::getInstance()->addInputFunction(shutdown);

	//

	Camera* camera = new Camera(0.0f, 0.0f, -3.0f);
	

	Texture* texture1 = new Texture("assets/container.jpg", JPG, GL_REPEAT);
	Texture* texture2 = new Texture("assets/confusion.png", PNG, GL_REPEAT);

	Shader texShader("src/shaders/tex.vert", "src/shaders/tex.frag");

	texShader.use();
	texShader.setInt("texture1", 0);
	texShader.setInt("texture2", 1);
	texShader.setFloat("mixValue", 0.5);


	Square* square = new Square(0.0f, 0.0f);
	Cube* cube = new Cube(0.0f, 0.0f);
	Cube* cube2 = new Cube(0.5f, 1.2f);

	square->texture.push_back(texture1->texture);
	square->texture.push_back(texture2->texture);

	while (!glfwWindowShouldClose(window.window))
	{
		inputListener.processInput(window.window);

		glClearColor(0.15f, 0.18f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);
		proj = glm::perspective(glm::radians(60.0f), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);
		view = camera->lookAt;
		texShader.setMat4("projection", proj);
		texShader.setMat4("view", view);

		square->setPosition(2.0f, 1.0f);
		texShader.setMat4("model", square->getPosition());

		square->draw();

		//cube->setPosition(2.0f, 0.0f);
		cube->setRotation(45.0f, glm::vec3(1.0, 0.0, 0.0), GL_TRUE);
		texShader.setMat4("model", cube->getPosition());
		cube->draw();

		cube2->setRotation((float)glfwGetTime()*0.7, glm::vec3(0.0, 1.0, 0.0), GL_FALSE);
		texShader.setMat4("model", cube2->getPosition());
		cube2->draw();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glfwPollEvents();
		glfwSwapBuffers(window.window);
	}

	glfwTerminate();
	return 0;
}