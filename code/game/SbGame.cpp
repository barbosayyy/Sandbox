
#include "Core/Base.h"
#include "Core/Debug.h"
#include "ECS/Components.h"
#include "Input/Input.h"
#include "Rendering/Primitive.h"
#include "Rendering/Renderer.h"
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"
#include "Resources/ShaderManager.h"
#include "stb_image/stb_image.h"
#include "Rendering/Camera.h"
#include "Rendering/Model.h"
#include "ECS/EntityManagement.h"

#include <cmath>
#include <string>

#include "Game/Game.h"
#include "SbGameBase.h"
#include "SbGameUI.h"

// ### TEMP - !!TEST!!
#include "ECS/Systems/RenderSystem.h"

using namespace Sb;

// Game scope variables
namespace SbGameGlobals{

	Shader* skyboxShader;
	Shader* geometryPassShader;
	Shader* lightingPassShader;

	unsigned int skyboxVAO, skyboxVBO;

	std::vector<vec3> lightPos;
	std::vector<vec3> lightCol;
	const u32 nrOfLights = 32;

	std::vector<Entity> lightVolumeSpheres;
	
	// TODO: Wrap Cubemap declaration 
		u32 cubemap;
		
		std::vector<String>faces = {
			"resources/assets/cubemap/right.jpg",
			"resources/assets/cubemap/left.jpg",
			"resources/assets/cubemap/top.jpg",
			"resources/assets/cubemap/bot.jpg",
			"resources/assets/cubemap/front.jpg",
			"resources/assets/cubemap/back.jpg"
		};

		u32 loadCubeMap(std::vector<String> faces) {
			u32 cbMap;
			glGenTextures(1, &cbMap);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cbMap);
			stbi_set_flip_vertically_on_load(false);
			int width, height, nChannels;
			for(u32 i = 0; i < faces.size(); i++){
				unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nChannels, 0);
				if(data){
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
				}	
				else{
					std::cout << "err texture" << std::endl;
					stbi_image_free(data);
				}
			}
			stbi_set_flip_vertically_on_load(true);

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

			return cbMap;
		}
}

using namespace SbGameGlobals;

Game::Game(IEngine& sbEngine) : _sbEngine(sbEngine) {
}

void Game::Init() {
}

void Game::Start() {
	
	geometryPassShader = _sbEngine.GetRenderer()._shaderManager.GetShader(3, 4);
	lightingPassShader = _sbEngine.GetRenderer()._shaderManager.GetShader(4, 6);

	// Cubemap
		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);
		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(SB_CUBE), &SB_CUBE, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		cubemap = loadCubeMap(faces);
		skyboxShader = _sbEngine.GetRenderer()._shaderManager.GetShader(1, 2);
		skyboxShader->SetInt("skybox", 0);

	// Objects

		Entity backpack = AddEntity();
		Entity cube = AddEntity();

		AddEntityComponent<TransformComponent>(backpack);
		AddEntityComponent<MeshComponent>(backpack);

		AddEntityComponent<TransformComponent>(cube);
		AddEntityComponent<MeshComponent>(cube);

		GetEntityComponent<MeshComponent>(backpack).model.LoadModel("resources/model/backpack.obj");

		GetEntityComponent<MeshComponent>(cube).model.LoadModel(Primitive::GetCube());

		Texture newTex = Texture("resources/assets/d_container.png", TextureType::DIFFUSE, GL_REPEAT, true, 0);

		GetEntityComponent<MeshComponent>(cube).model.GetMesh(0).SetTextureMap(newTex.GetID(), TextureType::DIFFUSE);

		GetEntityComponent<TransformComponent>(cube).pos.z = -1;
		
		GetEntityComponent<TransformComponent>(backpack).pos.x = 5;

	// Light pass prep

		lightingPassShader->Use();
		lightingPassShader->SetInt("gPosition", 0);
		lightingPassShader->SetInt("gNormal", 1);
		lightingPassShader->SetInt("gAlbedoSpec", 2);

		lightVolumeSpheres.reserve(nrOfLights);
		srand(13);
		for (unsigned int i = 0; i < nrOfLights; i++)
		{
			// calculate slightly random offsets
			float xPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			float yPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 4.0);
			float zPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			lightPos.push_back(glm::vec3(xPos, yPos, zPos));
			// also calculate random color
			float rColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5);
			float gColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5);
			float bColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5);
			lightCol.push_back(glm::vec3(rColor, gColor, bColor));
			Entity newSphere = AddEntity();
			AddEntityComponent<TransformComponent>(newSphere);
			GetEntityComponent<TransformComponent>(newSphere).pos = vec3(xPos, yPos, zPos);
			// AddEntityComponent<MeshComponent>(newSphere);
			// GetEntityComponent<MeshComponent>(newSphere).model.LoadModel(Primitive::GetSphere(1.0f, 36, 18));

			lightVolumeSpheres.emplace_back(newSphere);
		}

	SbGameUI::SetUIVisibility(false);

	Log::Info("SbGame: Started");
}

void Game::Update(){
	
}

void Game::Render() {

	// Geometry pass

	ECS::RenderSystem::Update(_sbEngine.GetECSRegistry());

	// backpack->Draw(geometryPassShader, &_sbEngine.GetRenderer(), vec3(0.0f, 0.0f, -3.0f));
	// backpack1->Draw(geometryPassShader, &_sbEngine.GetRenderer(), vec3(0.0f, 0.0f, -13.0f));
	// backpack2->Draw(geometryPassShader, &_sbEngine.GetRenderer(), vec3(0.0f, 0.0f, -23.0f));
	
	// Set lighting data and Light pass 
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	lightingPassShader->Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _sbEngine.GetRenderer().gPosition);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _sbEngine.GetRenderer().gNormal);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _sbEngine.GetRenderer().gAlbedoSpec);

	for(unsigned int i = 0; i < lightPos.size(); i++){
		lightingPassShader->SetVec3(String("lights[" + std::to_string(i) + "].position").c_str(), lightPos[i]);
		lightingPassShader->SetVec3(String("lights[" + std::to_string(i) + "].color").c_str(), lightCol[i]);
		const float constant = 1.0f;
		const float linear = 0.7f;
		const float quadratic = 1.8f;
		lightingPassShader->SetFloat(String("lights[" + std::to_string(i) + "].linear").c_str(), linear);
		lightingPassShader->SetFloat(String("lights[" + std::to_string(i) + "].quadratic").c_str(), quadratic);
		const float maxBrightness = std::fmaxf(std::fmaxf(lightCol[i].r, lightCol[i].g), lightCol[i].b);
		float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f/5.0f) * maxBrightness))) / (2.0f * quadratic);
		lightingPassShader->SetFloat(String("lights[" + std::to_string(i) + "].radius").c_str(), radius);
	}
	lightingPassShader->SetVec3("viewPos", _sbEngine.GetRenderer().GetRenderCamera()->_position);

	_sbEngine.GetRenderer().DrawFramebufferQuad(false);

	// Copy geometry depth to default framebuffer

	// Skybox pass

	glBindFramebuffer(GL_READ_FRAMEBUFFER, _sbEngine.GetRenderer()._gBuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	
	glBlitFramebuffer(0, 0, _sbEngine.GetRenderer().GetViewportWidth(), _sbEngine.GetRenderer().GetViewportHeight(), 0, 0, _sbEngine.GetRenderer().GetViewportWidth(), _sbEngine.GetRenderer().GetViewportHeight(), GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);
	skyboxShader->Use();
	glm::mat4 view = glm::mat4(glm::mat3(_sbEngine.GetRenderer().GetRenderCamera()->GetView()));
	skyboxShader->SetMat4("view", view);
	skyboxShader->SetMat4("projection", _sbEngine.GetRenderer().GetRenderCamera()->GetProjection());
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	SbGameUI::ShowUI(_sbEngine.GetRenderer().GetImGuiSbContext());
}

void Game::Stop() {
	Log::Info("SbGame: Stopping...");
}