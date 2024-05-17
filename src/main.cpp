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
#include "Core/Utils.h"
#include "Renderer/Model.h"

using namespace Sandbox;

float test1;
float test2;
float test3;

void ChangeSkbColor(){
	if(InputManager::PressedKey(SB_KEYBOARD_1)){
		test1 += 0.01f;
		Debugger::Print("test1: ", test1);
	}
	else if(InputManager::PressedKey(SB_KEYBOARD_2)){
		test2 += 0.01f;
		Debugger::Print("test2: ", test2);
	}
	else if(InputManager::PressedKey(SB_KEYBOARD_3)){
		test3 += 0.01f;	
		Debugger::Print("test3: ", test3);
	}	
	else if(InputManager::PressedKey(SB_KEYBOARD_4)){
		test1 -= 0.01f;
		Debugger::Print("test1: ", test1);
	}
	else if(InputManager::PressedKey(SB_KEYBOARD_5)){
		test2 -= 0.01f;	
		Debugger::Print("test2: ", test2);
	}	
	else if(InputManager::PressedKey(SB_KEYBOARD_6)){
		test3 -= 0.01f;
		Debugger::Print("test3: ", test3);
	}

	if(test1 > 1.0f)
		test1 = 0.0f;

	if(test2 > 1.0f)
		test2 = 0.0f;

	if(test3 > 1.0f)
		test3 = 0.0f;
}

void Shutdown(){
	Logger::Trace(LogLevel::RUNTIME, "Application Quit");
	glfwTerminate();
}

int main()
{
	Logger::Trace(LogLevel::RUNTIME, "Started Sandbox");
	Renderer* renderer = new Renderer();

	// ImGui
		ImGuiManager* imGuiManager = new ImGuiManager();
		imGuiManager->Init(renderer->GetWindow()->GLWindow(), SandboxImGuiStyle::IMGUI_DARK);
		InputManager* InputManager = InputManager::GetInstance(renderer->GetWindow()->GLWindow());
	
	Camera* camera = new Camera(0.0f, 0.0f, -3.0f);
	renderer->SetRenderCamera(camera);

	ShaderManager shaderManager = ShaderManager();
	//TextureManager textureManager = TextureManager();

	std::vector<Texture> txts{
		Texture("resources/assets/d_container.png", ImageFormat::PNG, TextureType::DIFFUSE, GL_REPEAT),
		Texture("resources/assets/s_container.png", ImageFormat::PNG, TextureType::SPECULAR, GL_REPEAT),
		Texture("resources/assets/matrix.jpg", ImageFormat::JPG, TextureType::EMISSIVE, GL_REPEAT)
	};
	Texture txt("resources/assets/confusion.png", ImageFormat::PNG, TextureType::DIFFUSE, GL_REPEAT);

	std::vector<Cube*> cubes = {};
	u16 nOfCubes = 20;
	for(u16 i = 0; i < nOfCubes; i++){
		Cube* newCube = new Cube(Random::GetRange(float(-5.0f), float(5.0f)), Random::GetRange(float(-5.0f), float(5.0f)), Random::GetRange(float(-5.0f), float(5.0f)));
		cubes.push_back(newCube);
		cubes.at(i)->RequestShader(2, 3, shaderManager);
		cubes.at(i)->SetMatRough(32.0f);
		cubes.at(i)->SetMatEm(1.0f);
		cubes.at(i)->AddMatTexture(txts.at(0));
		cubes.at(i)->SetRotation(Random::GetRange(float(5.0f), float(70.0f)), vec3(Random::GetRange(0, 1), Random::GetRange(0, 1), Random::GetRange(0, 1)), GL_TRUE);
		float a = Random::GetRange(float(0.2f), float(2.0f));
		cubes.at(i)->SetScale(a,a,a);
	}

	Cube* objLightBulb = new Cube(0.0f, 0.0f, 0.0f);
	objLightBulb->RequestShader(2, 2, shaderManager);
	objLightBulb->SetMatColor(1.0f,1.0f,1.0f);
	objLightBulb->SetScale(0.25f, 0.25f, 0.25f);

	Plane* plane = new Plane(0.0f, -5.0f, 0.0f);
	plane->RequestShader(2, 3, shaderManager);
	plane->AddMatTexture(txts.at(0));
	plane->SetMatRough(32.0f);
	plane->SetMatEm(1.0f);
	plane->SetScale(60.0f, 60.0f, 60.0f);

	Model* model = new Model("resources/model/backpack.obj");
	Shader* modelShader = new Shader("resources/shaders/model.vert", "resources/shaders/model.frag");

	Logger::Trace(LogLevel::RUNTIME, "Number of shaders: " ,shaderManager._shaderCount);
	Logger::Trace(LogLevel::RUNTIME, "Starting Sandbox Render Context...");
	while (!glfwWindowShouldClose(renderer->GetWindow()->GLWindow()))
	{
		InputManager->ProcessInput();

		ChangeSkbColor();
		glClearColor(test1, test2, test3, 1.0f);

		renderer->Loop();

		imGuiManager->NewRendererFrame();

		for(Cube* cube : cubes){
			cube->Draw(renderer);
		}

		objLightBulb->Draw(renderer);

		plane->Draw(renderer);

		modelShader->Use();
		modelShader->SetMat4("view", renderer->GetRenderCamera()->GetView());
		modelShader->SetMat4("projection", renderer->GetProjection());
		mat4 modelM {1.0f};
		modelM = glm::translate(modelM, vec3(0.0f,0.0f,0.0f));
		modelM = glm::scale(modelM, vec3(1.0f,1.0f,1.0f));
		shaderManager.GetShader(3,4)->SetMat4("model", modelM);

		model->Draw(modelShader);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		imGuiManager->RenderMain();
		glfwSwapBuffers(renderer->GetWindow()->GLWindow());
	}

	// delete objCube1;
	// delete objLightBulb;
	delete camera;
	delete InputManager;
	delete imGuiManager;
	delete renderer;

	Shutdown();
}