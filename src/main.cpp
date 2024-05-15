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
	Logger::Trace(LogLevel::INFO, "Application Quit");
	glfwTerminate();
}

int main()
{
	Renderer* renderer = new Renderer();

	// ImGui
		ImGuiManager* imGuiManager = new ImGuiManager();
		imGuiManager->Init(renderer->GetWindow()->GLWindow(), SandboxImGuiStyle::IMGUI_DARK);
		InputManager* InputManager = InputManager::GetInstance(renderer->GetWindow()->GLWindow());
	
	Camera* camera = new Camera(0.0f, 0.0f, -3.0f);
	renderer->SetRenderCamera(camera);

	ShaderManager shaderManager = ShaderManager();
	//TextureManager textureManager = TextureManager();

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
		litObject->RequestShader(2, 3, shaderManager);
		litObject->_mat.roughnessStrength = 32.0f;
		litObject->_mat.emissiveStrength = 1.0f;
		litObject->_mat.textures.push_back(txts.at(0)._texture);
		litObject->_mat.textures.push_back(txts.at(1)._texture);
		litObject->_mat.textures.push_back(txts.at(2)._texture);

		Cube* helloCube = new Cube(4.0f, 2.0f, 1.0f);
		helloCube->RequestShader(2, 3, shaderManager);
		helloCube->_mat.roughnessStrength = 32.0f;
		helloCube->_mat.emissiveStrength = 1.0f;
		//helloCube->_mat.textures.push_back(txts.at(0)._texture);
		//helloCube->_mat.textures.push_back(txts.at(1)._texture);
		//helloCube->_mat.textures.push_back(txts.at(2)._texture);

		helloCube->SetPosition(vec3(16.0f,2.0f,3.0f));
		helloCube->SetMatColor(1.0f,1.0f,1.0f);

	while (!glfwWindowShouldClose(renderer->GetWindow()->GLWindow()))
	{
		InputManager->ProcessInput();

		renderer->Loop();

		imGuiManager->NewRendererFrame();

		helloCube->Draw(renderer);
		litObject->Draw(renderer);

		// lightSource->_mat.shaders.at(0)->Use();
		// lightSource->_mat.shaders.at(0)->SetMat4("projection", projection);
		// lightSource->_mat.shaders.at(0)->SetMat4("view", renderer->GetRenderCamera()->GetView());
		// lightSource->_mat.shaders.at(0)->SetVec3("lightColor", lightColor.x, lightColor.y, lightColor.z);

		// lightSource->SetRotation(glfwGetTime(), Yaw_Right, GL_FALSE);
		// lightSource->SetScale(0.25f, 0.25f, 0.25f);
		// lightSource->_mat.shaders.at(0)->SetMat4("model", lightSource->GetModelMatrix());
		// lightSource->Draw();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		imGuiManager->RenderMain();

		glfwSwapBuffers(renderer->GetWindow()->GLWindow());
	}

	delete litObject;
	delete lightSource;
	delete camera;
	delete InputManager;
	delete imGuiManager;
	delete renderer;

	Shutdown();
}