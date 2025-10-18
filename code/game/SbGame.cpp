
#include "Core/Base.h"
#include "Core/Config.h"
#include "Core/Debug.h"
#include "ECS/Components.h"
#include "ECS/Registry.h"
#include "Input/Input.h"
#include "Rendering/Light.h"
#include "Rendering/Mesh.h"
#include "Rendering/Primitive.h"
#include "Rendering/Renderer.h"
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"
#include "Resources/ResourceManagement.h"
#include "stb_image/stb_image.h"
#include "Rendering/Camera.h"
#include "Rendering/Model.h"
#include "ECS/EntityManagement.h"
#include "Scene/SceneManagement.h"
#include "Resources/ResourceManifest.h"

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

	backpack = AddEntity();
	cube = AddEntity();
	skybox = AddEntity();
	light0 = AddEntity();
	light1 = AddEntity();
	light2 = AddEntity();

	AddEntityComponent<TransformComponent>(cube);
	AddEntityComponent<MeshComponent>(cube);
	GetEntityComponent<MeshComponent>(cube).model = ResourceManagement::LoadModel(SB_RESOURCE_MANIFEST_MESH_CUBE_ID);
	txtr = ResourceManagement::LoadTexture(15, TextureType::DIFFUSE);
	GetEntityComponent<MeshComponent>(cube).model->GetMeshes().at(0).SetTextureMap(txtr->id, txtr->type);
	GetEntityComponent<TransformComponent>(cube).pos = vec3(0, -2, -1);
	GetEntityComponent<TransformComponent>(cube).scale = vec3(0.5f);

	AddEntityComponent<TransformComponent>(backpack);
	AddEntityComponent<MeshComponent>(backpack);
	GetEntityComponent<MeshComponent>(backpack).model = ResourceManagement::LoadModel(24);
	GetEntityComponent<TransformComponent>(backpack).pos.x = 5;
	
	AddEntityComponent<SkyboxComponent>(skybox);
	GetEntityComponent<SkyboxComponent>(skybox).cubemap = ResourceManagement::LoadCubemap(13, 6, 14, 4, 5, 3);
	
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
		GetEntityComponent<TransformComponent>(light).pos = vec3(xPos, yPos, zPos);

		// also calculate random color
		float rColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5);
		float gColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5);
		float bColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5);
		GetEntityComponent<LightComponent>(light).light.color = vec3(rColor, gColor, bColor);
		GetEntityComponent<LightComponent>(light).light.intensity = 0.5f;
		GetEntityComponent<LightComponent>(light).light.range = 1;
	}

	GetEntityComponent<LightComponent>(light0).light->SetType(LightType::Point);

	SbGameUI::SetUIVisibility(false);

	Log::Info("SbGame: Started");
}

void Game::Update(){
	if(ping == true) {
		GetEntityComponent<TransformComponent>(cube).pos.x += 0.01f;
		if(GetEntityComponent<TransformComponent>(cube).pos.x >= 5) {
			ping = false;
		}
	}
	else {
		GetEntityComponent<TransformComponent>(cube).pos.x -= 0.01f;
		if(GetEntityComponent<TransformComponent>(cube).pos.x <= 0) {
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