#include <iostream>
#include <vector>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glew/glew.h>
#include <glfw/glfw3.h>

#include "math.h"
#include "window.h"
#include "shaders.h"
#include "input.h"
#include "primitives.h"
#include "camera.h"
#include "types.h"
#include "mesh.h"
#include "model.h"

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

	//ImGui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init();
		ImGui::StyleColorsDark();

		bool show_demo_window = true;
		bool show_another_window = false;
		bool show_third_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	Input::InputListener inputListener(window.window);
	Input::InputListener::getInstance()->addInputFunction(shutdown);
	
	//

	Camera* camera = new Camera(0.0f, 0.0f, -3.0f);

	// TODO: remove texture objects
	//Texture* T_tex1 = new Texture("assets/d_container.png", Texture::ImageType::PNG, GL_REPEAT);
	//Texture* T_tex2 = new Texture("assets/s_container.png", Texture::ImageType::PNG, GL_REPEAT);
	//Texture* T_tex3 = new Texture("assets/matrix.jpg", Texture::ImageType::JPG, GL_REPEAT);

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

	Cube* lightSource = new Cube(0.5f, 0.0f, 0.0f);

	std::vector<Texture> txts{
		Texture("assets/d_container.png", Texture::ImageType::PNG, Texture::TextureType::DIFFUSE, GL_REPEAT),
		Texture("assets/s_container.png", Texture::ImageType::PNG, Texture::TextureType::SPECULAR, GL_REPEAT),
		Texture("assets/matrix.jpg", Texture::ImageType::JPG, Texture::TextureType::EMISSIVE, GL_REPEAT)
	};

	std::vector<Vertex> vert{
		
	};
	std::vector<unsigned int> ind;

	Mesh test(vert, ind, txts, S_lighting);

	/*Cube* litObject = new Cube(2.5f, -1.0f, 1.0f);
	Cube* a = new Cube();
	Cube* b = new Cube();
	Cube* c = new Cube();*/

	// Spotlight values
	float spotlightInnerRadius{12.5f};
	float spotlightOuterRadius{17.5f};

	/*litObject->texture.push_back(T_tex1->texture);
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
	c->texture.push_back(T_tex3->texture);*/

	vec3 pointLightPositions[] =
	{
		vec3(0.7f,  0.2f,  2.0f),
		vec3(2.3f, -3.3f, -4.0f),
		vec3(-8.0f,  2.0f, -12.0f),
		vec3(0.0f,  0.0f, -3.0f)
	};

	while (!glfwWindowShouldClose(window.window))
	{
		glfwPollEvents();

		inputListener.processInput();
		
		// glClearColor(0.50f, 0.68f, 0.70f, 1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
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
			
		S_lighting.setFloat("material.shininess", 32.0f);
		S_lighting.setFloat("material.emissiveStrength", 1.0);


		S_lighting.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		S_lighting.setVec3("spotLight.diffuse", 0.0f, 0.0f, 0.0f);
		S_lighting.setVec3("spotLight.specular", 0.0f, 0.0f, 0.0f);

		S_lighting.setFloat("spotLight.constant", 1.0f);
		S_lighting.setFloat("spotLight.linear", 0.09f);
		S_lighting.setFloat("spotLight.quadratic", 0.032f);

		S_lighting.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		S_lighting.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		S_lighting.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		S_lighting.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
		
		S_lighting.setVec3("pointLight[0].position", pointLightPositions[0]);
		S_lighting.setVec3("pointLight[0].ambient", 0.05f, 0.05f, 0.05f);
		S_lighting.setVec3("pointLight[0].diffuse", 0.8f, 0.8f, 0.8f);
		S_lighting.setVec3("pointLight[0].specular", 1.0f, 1.0f, 1.0f);
		S_lighting.setFloat("pointLight[0].constant", 1.0f);
		S_lighting.setFloat("pointLight[0].linear", 0.09f);
		S_lighting.setFloat("pointLight[0].quadratic", 0.032f);

		S_lighting.setVec3("pointLight[1].position", pointLightPositions[1]);
		S_lighting.setVec3("pointLight[1].ambient", 0.05f, 0.05f, 0.05f);
		S_lighting.setVec3("pointLight[1].diffuse", 0.8f, 0.8f, 0.8f);
		S_lighting.setVec3("pointLight[1].specular", 1.0f, 1.0f, 1.0f);
		S_lighting.setFloat("pointLight[1].constant", 1.0f);
		S_lighting.setFloat("pointLight[1].linear", 0.09f);
		S_lighting.setFloat("pointLight[1].quadratic", 0.032f);

		S_lighting.setVec3("pointLight[2].position", pointLightPositions[2]);
		S_lighting.setVec3("pointLight[2].ambient", 0.05f, 0.05f, 0.05f);
		S_lighting.setVec3("pointLight[2].diffuse", 0.8f, 0.8f, 0.8f);
		S_lighting.setVec3("pointLight[2].specular", 1.0f, 1.0f, 1.0f);
		S_lighting.setFloat("pointLight[2].constant", 1.0f);
		S_lighting.setFloat("pointLight[2].linear", 0.09f);
		S_lighting.setFloat("pointLight[2].quadratic", 0.032f);

		S_lighting.setVec3("pointLight[3].position", pointLightPositions[3]);
		S_lighting.setVec3("pointLight[3].ambient", 0.05f, 0.05f, 0.05f);
		S_lighting.setVec3("pointLight[3].diffuse", 0.8f, 0.8f, 0.8f);
		S_lighting.setVec3("pointLight[3].specular", 1.0f, 1.0f, 1.0f);
		S_lighting.setFloat("pointLight[3].constant", 1.0f);
		S_lighting.setFloat("pointLight[3].linear", 0.09f);
		S_lighting.setFloat("pointLight[3].quadratic", 0.032f);

		S_lighting.setVec3("spotLight.direction", camera->front);
		S_lighting.setVec3("spotLight.position", camera->position);

		S_lighting.setFloat("spotLight.innerRadius", glm::cos(glm::radians(spotlightInnerRadius)));
		S_lighting.setFloat("spotLight.outerRadius", glm::cos(glm::radians(spotlightOuterRadius)));

		S_lighting.setVec3("viewer.position", camera->position.x, camera->position.y, camera->position.z);

		//litObject->setPosition(2.5f, -1.5f, 0.5f);
		//litObject->setRotation(45.0f, Yaw_Right, TRUE);
		//// This should be done when applying nonuniform scale to the object
		//mat4 normal{glm::inverseTranspose(litObject->getModelMatrix())};
		//S_lighting.setMat4("normalInverse", normal);
		//S_lighting.setMat4("model", litObject->getModelMatrix());
		//litObject->draw();

		//a->setPosition(5.0f, -1.5f, 2.0f);
		//a->setRotation(75.0f, Pitch_Up, TRUE);
		//normal = glm::inverseTranspose(a->getModelMatrix());
		//S_lighting.setMat4("normalInverse", normal);
		//S_lighting.setMat4("model", a->getModelMatrix());
		//a->draw();

		//b->setPosition(1.0f, -1.5f, 2.0f);
		//normal = glm::inverseTranspose(b->getModelMatrix());
		//S_lighting.setMat4("normalInverse", normal);
		//S_lighting.setMat4("model", b->getModelMatrix());
		//b->draw();

		//c->setPosition(4.0f, -5.0f, 5.0f);
		//c->setRotation(20.f, Yaw_Left, TRUE);
		//normal = glm::inverseTranspose(c->getModelMatrix());
		//S_lighting.setMat4("normalInverse", normal);
		//S_lighting.setMat4("model", c->getModelMatrix());
		//c->draw();

		S_light.use();
		S_light.setMat4("projection", projection);
		S_light.setMat4("view", view);
		S_light.setVec3("lightColor", lightColor.x, lightColor.y, lightColor.z);

		lightSource->setRotation(glfwGetTime(), Yaw_Right, GL_FALSE);
		lightSource->setScale(0.25f, 0.25f, 0.25f);
		S_light.setMat4("model", lightSource->getModelMatrix());
		lightSource->draw();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Sandbox");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window.window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}