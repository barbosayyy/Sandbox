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
#include "glfw/glfw3.h"
#include "glm/fwd.hpp"

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
	u16 nOfCubes = 6;
	for(u16 i = 0; i < nOfCubes; i++){
		Cube* newCube = new Cube(Random::GetRange(float(-5.0f), float(5.0f)), Random::GetRange(float(0), float(5.0f)), Random::GetRange(float(-5.0f), float(5.0f)));
		cubes.push_back(newCube);
		cubes.at(i)->RequestShader(2, 4, shaderManager);
		cubes.at(i)->GetMaterial().AddTexture(txts.at(0));
		cubes.at(i)->GetMaterial().AddTexture(txts.at(1));
		cubes.at(i)->SetRotation(Random::GetRange(float(5.0f), float(70.0f)), vec3(Random::GetRange(0, 1), Random::GetRange(0, 1), Random::GetRange(0, 1)), GL_TRUE);
		float a = Random::GetRange(float(0.2f), float(2.0f));
		cubes.at(i)->SetScale(a,a,a);
	}
	
	Cube* objLightBulb = new Cube(0.0f, 0.0f, 0.0f);
	objLightBulb->RequestShader(2, 3, shaderManager);
	objLightBulb->GetMaterial().SetColorOverlay(vec4(1.0f,1.0f,1.0f, 1.0f));
	objLightBulb->SetScale(0.25f, 0.25f, 0.25f);

	Plane* plane = new Plane(0.0f, -5.0f, 0.0f);
	plane->RequestShader(2, 4, shaderManager);
	plane->GetMaterial().AddTexture(txts.at(0));
	plane->GetMaterial().AddTexture(txts.at(1));
	plane->SetScale(32.0f, 32.0f, 32.0f);

	Square* square = new Square(0.0f, -1.0f, -12.0f);
	square->RequestShader(2,4,shaderManager);
	square->GetMaterial().AddTexture(txt);

	////////////////////////////////////////////////////////////////////////////////////////////
	
	Shader* screenShader = shaderManager.GetShader(4, 7);
	screenShader->Use();
	screenShader->SetInt("screenTexture", 0);

	Shader* rearViewShader = shaderManager.GetShader(4, 6);
	rearViewShader->Use();
	rearViewShader->SetInt("screenTexture", 0);

	u32 fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	u32 texColorBuffer;
	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, renderer->GetWindow()->GetWidth(), renderer->GetWindow()->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0); 

	u32 rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, renderer->GetWindow()->GetWidth(), renderer->GetWindow()->GetHeight());

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		Debugger::Print("Framebuffer not ready!");	
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	// u32 rearViewFbo;
	// glGenFramebuffers(1, &rearViewFbo);
	// glBindFramebuffer(GL_FRAMEBUFFER, rearViewFbo);

	// u32 rearViewTexture;
	// glGenTextures(1, &rearViewTexture);
	// glBindTexture(GL_TEXTURE_2D, rearViewTexture);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 600, 400, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rearViewTexture, 0); 

	// u32 rearViewRbo;
	// glGenRenderbuffers(1, &rearViewRbo);
	// glBindRenderbuffer(GL_RENDERBUFFER, rearViewRbo);
	// glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 600, 400);

	// glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rearViewRbo);

	// if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
	// 	Debugger::Print("Framebuffer not ready!");	
	// }
	// glBindFramebuffer(GL_FRAMEBUFFER, 0);




	// This could be wrapped

	float SB_QUAD[] = {
	-1.0f,  1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 1.0f};

	float SB_QUAD2[] = {
	-0.3f,  1.0f,  0.0f, 1.0f,
        -0.3f,  0.7f,  0.0f, 0.0f,
         0.3f,  0.7f,  1.0f, 0.0f,

        -0.3f,  1.0f,  0.0f, 1.0f,
         0.3f,  0.7f,  1.0f, 0.0f,
         0.3f,  1.0f,  1.0f, 1.0f};

	unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SB_QUAD), &SB_QUAD, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	unsigned int quadVAO2, quadVBO2;
    glGenVertexArrays(1, &quadVAO2);
    glGenBuffers(1, &quadVBO2);
    glBindVertexArray(quadVAO2);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SB_QUAD2), &SB_QUAD2, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	////////////////////////////////////////////////////////////////////////////////////////////

	Logger::Trace(LogLevel::RUNTIME, "Number of shaders: " ,shaderManager._shaderCount);
	Logger::Trace(LogLevel::RUNTIME, "Starting Sandbox Render Context...");
	

	renderer->Setup();

	Camera* rearViewCamera= new Camera(renderer->GetRenderCamera()->_position.x, renderer->GetRenderCamera()->_position.y, renderer->GetRenderCamera()->_position.z);

	// rearViewCamera._lookAt = glm::lookAt(_position, _position + _front, _up);

	while (!glfwWindowShouldClose(renderer->GetWindow()->GLWindow()))
	{
		InputManager->ProcessInput();

		// renderer->Loop();

		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		imGuiManager->NewRendererFrame();

		plane->Draw(renderer);
		for(Cube* cube : cubes){
			cube->Draw(renderer);
		}
		objLightBulb->Draw(renderer);
		square->Draw(renderer);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);
		screenShader->Use();
		glBindVertexArray(quadVAO);
		glBindTexture(GL_TEXTURE_2D, texColorBuffer);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		imGuiManager->RenderMain();

		glfwPollEvents();
		glfwSwapBuffers(renderer->GetWindow()->GLWindow());
	}

	delete objLightBulb;
	delete camera;
	delete InputManager;
	delete imGuiManager;
	delete renderer;

	Shutdown();
}