
#include "Core/Base.h"
#include "Core/Config.h"
#include "Core/Debug.h"
#include "Core/Utils.h"
#include "Input/Input.h"
#include "ECS/Components.h"
#include "ECS/Registry.h"
#include "Rendering/Light.h"
#include "Rendering/Mesh.h"
#include "Rendering/Texture.h"
#include "Resources/Primitive.h"
#include "Resources/ResourceManagement.h"
#include "Rendering/Model.h"
#include "ECS/EntityManagement.h"
#include "Scene/SceneManagement.h"
#include "Resources/ResourceManifest.h"
#include "Game/Game.h"

#include "stb_image/stb_image.h"

#include "SbGameBase.h"
#include "SbGameUI.h"

using namespace Sb;

// Game scope variables
namespace SbGameGlobals{

	Entity backpack;
	Entity cube;
	Entity skybox;
	Entity plane;

	bool ping = true;

	Texture* txtr;
		
}

using namespace SbGameGlobals;

Game::Game(IEngine& sbEngine) : _sbEngine(sbEngine) {
}

void Game::Init() {
}

void Game::Start() {

	plane = AddEntity();
	backpack = AddEntity();
	cube = AddEntity();
	skybox = AddEntity();

	AddEntityComponent<TransformComponent>(cube);
	AddEntityComponent<MeshComponent>(cube);
	GetEntityComponent<MeshComponent>(cube).model = ResourceManagement::LoadModel(Primitive::GetCube());
	txtr = ResourceManagement::LoadTexture("assets/d_container.png", TextureType::DIFFUSE);
	GetEntityComponent<MeshComponent>(cube).model->GetMeshes().at(0).SetTextureMap(txtr->id, txtr->type);
	GetEntityComponent<TransformComponent>(cube).position = vec3(0, -2, -1);
	GetEntityComponent<TransformComponent>(cube).scale = vec3(0.5f);

	AddEntityComponent<TransformComponent>(backpack);
	AddEntityComponent<MeshComponent>(backpack);
	GetEntityComponent<MeshComponent>(backpack).model = ResourceManagement::LoadModel("model/backpack.obj");
	GetEntityComponent<TransformComponent>(backpack).position.x = 5;

	AddEntityComponent<SkyboxComponent>(skybox);
	GetEntityComponent<SkyboxComponent>(skybox).cubemap = ResourceManagement::LoadCubemap(
		"assets/cubemap/right.jpg", "assets/cubemap/left.jpg",
		"assets/cubemap/top.jpg", "assets/cubemap/bot.jpg",
		"assets/cubemap/front.jpg", "assets/cubemap/back.jpg");
	
	AddEntityComponent<TransformComponent>(plane);
	AddEntityComponent<MeshComponent>(plane);
	GetEntityComponent<MeshComponent>(plane).model = ResourceManagement::LoadModel(Primitive::GetPlane());
	GetEntityComponent<MeshComponent>(plane).model->GetMeshes().at(0).SetTextureMap(txtr->id, txtr->type);
	GetEntityComponent<TransformComponent>(plane).position.y = -6;
	GetEntityComponent<TransformComponent>(plane).scale.x = 10;
	GetEntityComponent<TransformComponent>(plane).scale.z = 10;
	
	/*
		Number of LightComponent entities defines numLights
		Non UBO lights should have a different approach
	*/

	u32 numLightEntities = 32;

	srand(13);
	for (unsigned int i = 0; i < numLightEntities; i++)
	{
		// calculate slightly random offsets
		Entity light = AddEntity();
		AddEntityComponent<TransformComponent>(light);
		AddEntityComponent<LightComponent>(light);

		float xPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
		float yPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 4.0);
		float zPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
		GetEntityComponent<TransformComponent>(light).position = vec3(xPos, yPos, zPos);

		// also calculate random color
		float rColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5);
		float gColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5);
		float bColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5);
		GetEntityComponent<LightComponent>(light).light.color = vec3(rColor, gColor, bColor);
		GetEntityComponent<LightComponent>(light).light.intensity = 0.5f;
		GetEntityComponent<LightComponent>(light).light.range = 1;
	}

	SbGameUI::SetUIVisibility(false);

	Log::Info("SbGame: Started");
}

void Game::Update(){
	if(ping == true) {
		GetEntityComponent<TransformComponent>(cube).position.x += 0.01f;
		if(GetEntityComponent<TransformComponent>(cube).position.x >= 5) {
			ping = false;
		}
	}
	else {
		GetEntityComponent<TransformComponent>(cube).position.x -= 0.01f;
		if(GetEntityComponent<TransformComponent>(cube).position.x <= 0) {
			ping = true;
		}
	}
}

// void Game::Render(){
// 	SbGameUI::ShowUI(_sbEngine.GetRenderer().GetImGuiSbContext());
// }

void Game::Stop(){
	Log::Info("SbGame: Stopping...");
}