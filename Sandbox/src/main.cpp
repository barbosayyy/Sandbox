#include <iostream>
#include <vector>

#include <glew/glew.h>
#include <glfw/glfw3.h>

#include "math.h"
#include "window.h"
#include "shaders.h"
#include "input.h"
#include "primitives.h"
#include "camera.h"
#include "types.h"

void shutdown()
{
	if (Input::pressedKey(GLFW_KEY_ESCAPE))
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

	// TODO: remove texture objects
	Texture* T_tex1 = new Texture("assets/d_container.png", Texture::ImageType::PNG, GL_REPEAT);
	Texture* T_tex2 = new Texture("assets/s_container.png", Texture::ImageType::PNG, GL_REPEAT);
	Texture* T_tex3 = new Texture("assets/matrix.jpg", Texture::ImageType::JPG, GL_REPEAT);

	//	Shader S_tex("src/shaders/tex.vert", "src/shaders/tex.frag");
	//	S_tex.use();
	//	S_tex.setInt("texture1", 0);
	//	S_tex.setInt("texture2", 1);
	//	S_tex.setFloat("mixValue", 0.0f);

	vec3 lightColor(1.0f, 1.0f, 1.0f);

	Shader S_light("src/shaders/material.vert", "src/shaders/light.frag");
	Shader S_lighting("src/shaders/material.vert", "src/shaders/lit.frag");

	S_lighting.use();
	S_lighting.setInt("material.diffuse", 0);
	S_lighting.setInt("material.specular", 1);
	S_lighting.setInt("material.emissive", 2);

	Cube* litObject = new Cube(2.5f, -1.0f, 1.0f);
	Cube* lightSource = new Cube(0.5f, 0.0f, 0.0f);
	Cube* a = new Cube();
	Cube* b = new Cube();
	Cube* c = new Cube();

	// Spotlight values
	float spotlightInnerRadius{12.5f};
	float spotlightOuterRadius{17.5f};

	litObject->texture.push_back(T_tex1->texture);
	litObject->texture.push_back(T_tex2->texture);
	litObject->texture.push_back(T_tex3->texture);	

	a->texture.push_back(T_tex1->texture);
	a->texture.push_back(T_tex2->texture);
	a->texture.push_back(T_tex3->texture);

	b->texture.push_back(T_tex1->texture);
	b->texture.push_back(T_tex2->texture);
	b->texture.push_back(T_tex3->texture);

	c->texture.push_back(T_tex1->texture);
	c->texture.push_back(T_tex2->texture);
	c->texture.push_back(T_tex3->texture);

	while (!glfwWindowShouldClose(window.window))
	{
		inputListener.processInput();
		
		// glClearColor(0.50f, 0.68f, 0.70f, 1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glEnable(GL_DEPTH_TEST);

		// glEnable(GL_CULL_FACE);
		// glCullFace(GL_BACK);

		mat4 view = mat4(1.0f);
		mat4 projection = mat4(1.0f);
		projection = glm::perspective(glm::radians(60.0f), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);
		view = camera->lookAt;
		
		S_lighting.use();
		S_lighting.setMat4("view", view);
		S_lighting.setMat4("projection", projection);
			
		// Material
			S_lighting.setFloat("material.shininess", 32.0f);
			S_lighting.setFloat("material.emissiveStrength", 1.0);

		// Light
			S_lighting.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
			S_lighting.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
			S_lighting.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

			// Point and Spot
			S_lighting.setFloat("light.constant", 1.0f);
			S_lighting.setFloat("light.linear", 0.09f);
			S_lighting.setFloat("light.quadratic", 0.032f);

			// Point
			//S_lighting.setVec3("light.position", lightSource->getPosition().x, lightSource->getPosition().y, lightSource->getPosition().z);

			// Spot
			S_lighting.setVec3("light.direction", camera->front);
			S_lighting.setVec3("light.position", camera->position);
			S_lighting.setFloat("light.innerRadius", glm::cos(glm::radians(spotlightInnerRadius)));
			S_lighting.setFloat("light.outerRadius", glm::cos(glm::radians(spotlightOuterRadius)));

			// Directional
			//S_lighting.setVec3("light.direction", -0.2, -1.0f, -0.3f);

		S_lighting.setVec3("viewer.position", camera->position.x, camera->position.y, camera->position.z);

		litObject->setPosition(2.5f, -1.5f, 0.5f);
		litObject->setRotation(45.0f, Yaw_Right, TRUE);
		// This should be done when applying nonuniform scale to the object
		mat4 normal{glm::inverseTranspose(litObject->getModelMatrix())};
		S_lighting.setMat4("normalInverse", normal);
		S_lighting.setMat4("model", litObject->getModelMatrix());
		litObject->draw();

		a->setPosition(5.0f, -1.5f, 2.0f);
		a->setRotation(75.0f, Pitch_Up, TRUE);
		normal = glm::inverseTranspose(a->getModelMatrix());
		S_lighting.setMat4("normalInverse", normal);
		S_lighting.setMat4("model", a->getModelMatrix());
		a->draw();

		b->setPosition(1.0f, -1.5f, 2.0f);
		normal = glm::inverseTranspose(b->getModelMatrix());
		S_lighting.setMat4("normalInverse", normal);
		S_lighting.setMat4("model", b->getModelMatrix());
		b->draw();

		c->setPosition(4.0f, -5.0f, 5.0f);
		c->setRotation(20.f, Yaw_Left, TRUE);
		normal = glm::inverseTranspose(c->getModelMatrix());
		S_lighting.setMat4("normalInverse", normal);
		S_lighting.setMat4("model", c->getModelMatrix());
		c->draw();

		S_light.use();
		S_light.setMat4("projection", projection);
		S_light.setMat4("view", view);
		S_light.setVec3("lightColor", lightColor.x, lightColor.y, lightColor.z);

		lightSource->setRotation(glfwGetTime(), Yaw_Right, GL_FALSE);
		lightSource->setScale(0.25f, 0.25f, 0.25f);
		S_light.setMat4("model", lightSource->getModelMatrix());
		lightSource->draw();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glfwPollEvents();
		glfwSwapBuffers(window.window);
	}

	glfwTerminate();
	return 0;
}