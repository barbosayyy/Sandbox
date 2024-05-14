#include "Core/Base.h"

#include "Renderer/Renderer.h"
#include "ImGui/ImGuiManager.h"
#include "Math/Vectors.h"
#include "Renderer/Texture.h"
#include "Renderer/Window.h"
#include "Renderer/Shader.h"
#include "Input/Input.h"
#include "Renderer/Primitives.h"
#include "Renderer/Camera.h"
#include "Core/Types.h"
#include "Core/Debug.h"

using namespace Sandbox;

void Shutdown(){
	if (InputManager::PressedKey(SB_KEYBOARD_ESCAPE)){
		glfwTerminate();
		Logger::Trace(LogLevel::INFO, "Application Quit");
		std::exit(0);
	}
}

int main()
{
	Renderer* renderer = new Renderer();

	// ImGui
		ImGuiManager* imGuiManager = new ImGuiManager();
		imGuiManager->Init(renderer->GetWindow()->GLWindow(), SandboxImGuiStyle::IMGUI_DARK);
		InputManager* InputManager = InputManager::GetInstance(renderer->GetWindow()->GLWindow());
		InputManager->GetInstance()->AddInputFunction(Shutdown);

	Camera* camera = new Camera(0.0f, 0.0f, -3.0f);

	// Temp
	Shader* S_light = new Shader("resources/shaders/material.vert", "resources/shaders/light.frag");
	Shader* S_lighting = new Shader("resources/shaders/material.vert", "resources/shaders/lit.frag");

	ShaderManager shaderManager = ShaderManager();
	//TextureManager textureManager = TextureManager();

	//shaderManager.AddShader(S_light);
	//shaderManager.AddShader(S_lighting);

	S_lighting->Use();
	S_lighting->SetInt("material.diffuse", 0);
	S_lighting->SetInt("material.specular", 1);
	S_lighting->SetInt("material.emissive", 2);

	Cube* lightSource = new Cube(0.5f, 0.0f, 0.0f);

	lightSource->RequestShader(2, 2, shaderManager);

	std::vector<Texture> txts{
		Texture("resources/assets/d_container.png", ImageFormat::PNG, TextureType::DIFFUSE, GL_REPEAT),
		Texture("resources/assets/s_container.png", ImageFormat::PNG, TextureType::SPECULAR, GL_REPEAT),
		Texture("resources/assets/matrix.jpg", ImageFormat::JPG, TextureType::EMISSIVE, GL_REPEAT)
	};
	
	// Objects
		// Mesh Test
		// 	std::vector<Vertex> vert{
		// 		
		// 	};
		// 	std::vector<unsigned int> ind;
		// 	Mesh test(vert, ind, txts, S_lighting);
		
		Cube* litObject = new Cube(2.5f, -1.0f, 1.0f);
		litObject->_mat._texture.push_back(txts.at(0)._texture);
		litObject->_mat._texture.push_back(txts.at(1)._texture);
		litObject->_mat._texture.push_back(txts.at(2)._texture);

		//litObject->RequestShader(0, shaderManager);

	// Light
		vec3 lightColor(1.0f, 1.0f, 1.0f);
		float spotlightInnerRadius{12.5f};
		float spotlightOuterRadius{17.5f};
		vec3 pointLightPositions[] =
		{
			vec3(0.5f, 0.0f, 0.0f)
		};

	while (!glfwWindowShouldClose(renderer->GetWindow()->GLWindow()))
	{
		InputManager->ProcessInput();
		
		// Temp
		renderer->Loop();
		// Everything below rendering-wise should be encapsulated by the renderer
		
		imGuiManager->NewRendererFrame();

		mat4 view = mat4(1.0f);	
		mat4 projection = mat4(1.0f);
		projection = glm::perspective(glm::radians(60.0f), (float)renderer->GetWindow()->GetWidth() / (float)renderer->GetWindow()->GetHeight(), 0.1f, 100.0f);
		view = camera->_lookAt;
		
		// Shader
			S_lighting->Use();
			S_lighting->SetMat4("view", view);
			S_lighting->SetMat4("projection", projection);
			
			S_lighting->SetFloat("material.shininess", 32.0f);
			S_lighting->SetFloat("material.emissiveStrength", 1.0);

			S_lighting->SetVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
			S_lighting->SetVec3("spotLight.diffuse", 0.0f, 0.0f, 0.0f);
			S_lighting->SetVec3("spotLight.specular", 0.0f, 0.0f, 0.0f);

			S_lighting->SetFloat("spotLight.constant", 1.0f);
			S_lighting->SetFloat("spotLight.linear", 0.09f);
			S_lighting->SetFloat("spotLight.quadratic", 0.032f);

			S_lighting->SetVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
			S_lighting->SetVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
			S_lighting->SetVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
			S_lighting->SetVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
		
			S_lighting->SetVec3("pointLight[0].position", pointLightPositions[0]);
			S_lighting->SetVec3("pointLight[0].ambient", 0.05f, 0.05f, 0.05f);
			S_lighting->SetVec3("pointLight[0].diffuse", 0.8f, 0.8f, 0.8f);
			S_lighting->SetVec3("pointLight[0].specular", 1.0f, 1.0f, 1.0f);
			S_lighting->SetFloat("pointLight[0].constant", 1.0f);
			S_lighting->SetFloat("pointLight[0].linear", 0.09f);
			S_lighting->SetFloat("pointLight[0].quadratic", 0.032f);

			S_lighting->SetVec3("spotLight.direction", camera->_front);
			S_lighting->SetVec3("spotLight.position", camera->_position);

			S_lighting->SetFloat("spotLight.innerRadius", glm::cos(glm::radians(spotlightInnerRadius)));
			S_lighting->SetFloat("spotLight.outerRadius", glm::cos(glm::radians(spotlightOuterRadius)));

			S_lighting->SetVec3("viewer.position", camera->_position.x, camera->_position.y, camera->_position.z);

		//litObject->setPosition(2.5f, -1.5f, 0.5f);
		//litObject->setRotation(45.0f, Yaw_Right, TRUE);
		//// This should be done when applying nonuniform scale to the object
		mat4 normal{glm::inverseTranspose(litObject->GetModelMatrix())};
		S_lighting->SetMat4("normalInverse", normal);
		S_lighting->SetMat4("model", litObject->GetModelMatrix());
		litObject->Draw();

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

		S_light->Use();
		S_light->SetMat4("projection", projection);
		S_light->SetMat4("view", view);
		S_light->SetVec3("lightColor", lightColor.x, lightColor.y, lightColor.z);

		lightSource->SetRotation(glfwGetTime(), Yaw_Right, GL_FALSE);
		lightSource->SetScale(0.25f, 0.25f, 0.25f);
		S_light->SetMat4("model", lightSource->GetModelMatrix());
		lightSource->Draw();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		imGuiManager->RenderMain();

		glfwSwapBuffers(renderer->GetWindow()->GLWindow());
	}

	delete S_lighting;
	delete S_light;
	delete litObject;
	delete lightSource;
	delete imGuiManager;
	delete camera;
	delete renderer;

	Shutdown();
}