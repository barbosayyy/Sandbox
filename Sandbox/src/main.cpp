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
	if (Input::pressedKey(GLFW_KEY_ESCAPE))
	{
		glfwTerminate();
	}
}

void mouseCallback(GLFWwindow* window);

void mouseCallback(GLFWwindow* window) {
	// Your callback logic here
}

int main(void)
{
	// GLFW initialization
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	Window window("Sandbox", WINDOW_WIDTH, WINDOW_HEIGHT);

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

	Texture* T_tex1 = new Texture("assets/container.jpg", Texture::ImageType::JPG, GL_REPEAT);
	Texture* T_tex2 = new Texture("assets/confusion.png", Texture::ImageType::PNG, GL_REPEAT);
	Shader S_tex("src/shaders/tex.vert", "src/shaders/tex.frag");
	S_tex.use();
	S_tex.setInt("texture1", 0);
	S_tex.setInt("texture2", 1);
	S_tex.setFloat("mixValue", 1.0f);

	Square* square = new Square(0.0f, 0.0f);
	Cube* cube = new Cube(0.0f, 0.0f);
	Cube* cube2 = new Cube(0.5f, 1.2f);
	Square2* square2 = new Square2(3.0f, 0.0f);
	square->texture.push_back(T_tex1->texture);
	square->texture.push_back(T_tex2->texture);
	square2->texture.push_back(T_tex1->texture);
	square2->texture.push_back(T_tex2->texture);

	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	glm::vec3 objectColor(54/255, 156/255, 81/255);
	glm::vec3 result = lightColor * objectColor;

	while (!glfwWindowShouldClose(window.window))
	{
		inputListener.processInput();

		glClearColor(0.15f, 0.18f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);
		proj = glm::perspective(glm::radians(60.0f), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);
		view = camera->lookAt;

		S_tex.setMat4("projection", proj);
		S_tex.setMat4("view", view);

		square->setPosition(2.0f, 1.0f);
		S_tex.setMat4("model", square->getPosition());
		square->draw();

		cube->setPosition(2.0f, 0.0f);
		cube->setRotation(45.0f, glm::vec3(1.0, 0.0, 0.0), GL_TRUE);
		S_tex.setMat4("model", cube->getPosition());
		cube->draw();

		cube2->setRotation((float)glfwGetTime()*0.7, glm::vec3(0.0, 1.0, 0.0), GL_FALSE);
		S_tex.setMat4("model", cube2->getPosition());
		cube2->draw();

		S_tex.setMat4("model", square2->getPosition());
		square2->draw();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glfwPollEvents();
		glfwSwapBuffers(window.window);
	}

	glfwTerminate();
	return 0;
}