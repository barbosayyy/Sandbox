#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/matrix_inverse.hpp>

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
		glfwTerminate();
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
	Texture* T_tex2 = new Texture("assets/test.png", Texture::ImageType::PNG, GL_REPEAT);

	Shader S_tex("src/shaders/tex.vert", "src/shaders/tex.frag");
	S_tex.use();
	S_tex.setInt("texture1", 0);
	S_tex.setInt("texture2", 1);
	S_tex.setFloat("mixValue", 0.0f);

	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

	Shader S_light("src/shaders/color.vert", "src/shaders/light_source.frag");
	Shader S_lighting("src/shaders/color.vert", "src/shaders/lit.frag");

	Cube* litObject = new Cube(2.5f, -1.0f, 1.0f);
	Cube* lightSource = new Cube(0.5f, 0.0f, 0.0f);
	Square* Plane = new Square(0.0f, -5.0f, 0.0f);
	Plane->setScale(20.0f, 20.0f, 1.0f);
	Plane->setRotation(90.0f, glm::vec3(1.0f, 0.0f, 0.0f), GL_TRUE);
	Plane->texture.push_back(T_tex1->texture);
	Plane->texture.push_back(T_tex2->texture);

	while (!glfwWindowShouldClose(window.window))
	{
		inputListener.processInput();

		glClearColor(0.50f, 0.68f, 0.96f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(60.0f), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);
		view = camera->lookAt;

		S_lighting.use();
		S_lighting.setMat4("view", view);
		S_lighting.setMat4("projection", projection);

		S_lighting.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
		S_lighting.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
		S_lighting.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		S_lighting.setFloat("material.shininess", 32.0f);

		S_lighting.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		S_lighting.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		S_lighting.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

		S_lighting.setVec3("light.position", lightSource->getPosition().x, lightSource->getPosition().y, lightSource->getPosition().z);
		S_lighting.setVec3("viewer.position", camera->position.x, camera->position.y, camera->position.z);
		// This should be done when applying nonuniform scale to the object
		glm::mat4 normal{glm::inverseTranspose(litObject->getModelMatrix())};
		S_lighting.setMat4("normalInverse", normal);

		litObject->setPosition(2.5f, -1.5f, 0.5f);	
		litObject->setRotation(40.0f, glm::vec3(1.0f,1.0f,0.0f), 2.0f);
		S_lighting.setMat4("model", litObject->getModelMatrix());
		litObject->draw();

		S_light.use();
		S_light.setMat4("projection", projection);
		S_light.setMat4("view", view);
		S_light.setVec3("lightColor", lightColor.x, lightColor.y, lightColor.z);
		//lightSource->setRotation((float)glfwGetTime()*0.7, glm::vec3(0.0, 1.0, 0.0), GL_FALSE);
		
		//TODO:
		//	Check again setpos, rot and scale order of operation
		//	Add setScale function to shader class
		

		lightSource->setRotation(glfwGetTime(), glm::vec3(0.0, 1.0, 0.0), GL_FALSE);
		lightSource->setScale(0.25f, 0.25f, 0.25f);
		S_light.setMat4("model", lightSource->getModelMatrix());
		lightSource->draw();

		S_lighting.use();
		S_lighting.setMat4("model", Plane->getModelMatrix());
		Plane->draw();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glfwPollEvents();
		glfwSwapBuffers(window.window);
	}

	glfwTerminate();
	return 0;
}