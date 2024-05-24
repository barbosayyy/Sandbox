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
	renderer->GetRenderCamera()->_moveSpeed = 0.025;

	ShaderManager shaderManager = ShaderManager();
	//TextureManager textureManager = TextureManager();

	std::vector<Texture> txts{
		Texture("resources/assets/d_container.png", TextureType::DIFFUSE, GL_REPEAT, true, 0),
		Texture("resources/assets/s_container.png", TextureType::SPECULAR, GL_REPEAT, true, 0),
		Texture("resources/assets/matrix.jpg", TextureType::EMISSIVE, GL_REPEAT, true, 0)
	};
	Texture txt("resources/assets/confusion.png", TextureType::DIFFUSE, GL_CLAMP_TO_EDGE, true, 0);

	std::vector<Cube*> cubes = {};
	u16 nOfCubes = 100;
	for(u16 i = 0; i < nOfCubes; i++){
		Cube* newCube = new Cube(Random::GetRange(float(-5.0f), float(5.0f)), Random::GetRange(float(-5.0f), float(5.0f)), Random::GetRange(float(-5.0f), float(5.0f)));
		cubes.push_back(newCube);
		cubes.at(i)->RequestShader(2, 4, shaderManager);
		cubes.at(i)->SetMatRough(32.0f);
		cubes.at(i)->SetMatEm(1.0f);
		cubes.at(i)->AddMatTexture(txts.at(0));
		cubes.at(i)->AddMatTexture(txts.at(1));
		cubes.at(i)->SetRotation(Random::GetRange(float(5.0f), float(70.0f)), vec3(Random::GetRange(0, 1), Random::GetRange(0, 1), Random::GetRange(0, 1)), GL_TRUE);
		float a = Random::GetRange(float(0.2f), float(2.0f));
		cubes.at(i)->SetScale(a,a,a);
	}

	Cube* objLightBulb = new Cube(0.0f, 0.0f, 0.0f);
	objLightBulb->RequestShader(2, 3, shaderManager);
	objLightBulb->SetMatColor(1.0f,1.0f,1.0f);
	objLightBulb->SetScale(0.25f, 0.25f, 0.25f);

	Plane* plane = new Plane(0.0f, -5.0f, 0.0f);
	plane->RequestShader(2, 4, shaderManager);
	plane->AddMatTexture(txts.at(0));
	plane->AddMatTexture(txts.at(1));
	plane->SetMatRough(32.0f);
	plane->SetMatEm(1.0f);
	plane->SetScale(32.0f, 32.0f, 32.0f);

	Square* square = new Square(0.0f, -1.0f, -12.0f);
	square->RequestShader(2,4,shaderManager);
	square->AddMatTexture(txt);
	square->SetMatRough(64.0f);
	square->SetMatEm(1.0f);

	Logger::Trace(LogLevel::RUNTIME, "Number of shaders: " ,shaderManager._shaderCount);
	Logger::Trace(LogLevel::RUNTIME, "Starting Sandbox Render Context...");
	renderer->Setup();

	while (!glfwWindowShouldClose(renderer->GetWindow()->GLWindow()))
	{
		InputManager->ProcessInput();

		renderer->Loop();

		imGuiManager->NewRendererFrame();

		plane->Draw(renderer);

		for(Cube* cube : cubes){
			cube->Draw(renderer);
		}

		objLightBulb->Draw(renderer);

		square->Draw(renderer);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		imGuiManager->RenderMain();
		glfwSwapBuffers(renderer->GetWindow()->GLWindow());
	}

	delete objLightBulb;
	delete camera;
	delete InputManager;
	delete imGuiManager;
	delete renderer;

	Shutdown();
}