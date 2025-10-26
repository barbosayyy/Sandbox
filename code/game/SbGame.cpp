
#include "Core/Base.h"
#include "Core/Config.h"
#include "Core/Debug.h"
#include "Input/Input.h"
#include "ECS/Components.h"
#include "ECS/Registry.h"
#include "Rendering/Light.h"
#include "Rendering/Mesh.h"
#include "Rendering/Texture.h"
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

	Entity parent0;
	Entity parent1;
	Entity child0;
	Entity child1;

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
	plane = AddEntity();

	AddEntityComponent<TransformComponent>(cube);
	AddEntityComponent<MeshComponent>(cube);
	GetEntityComponent<MeshComponent>(cube).model = ResourceManagement::LoadModel(SB_RESOURCE_MANIFEST_MESH_CUBE_ID);
	txtr = ResourceManagement::LoadTexture(15, TextureType::DIFFUSE);
	GetEntityComponent<MeshComponent>(cube).model->GetMeshes().at(0).SetTextureMap(txtr->id, txtr->type);
	GetEntityComponent<TransformComponent>(cube).position = vec3(0, -2, -1);
	GetEntityComponent<TransformComponent>(cube).scale = vec3(0.5f);

	AddEntityComponent<TransformComponent>(backpack);
	AddEntityComponent<MeshComponent>(backpack);
	GetEntityComponent<MeshComponent>(backpack).model = ResourceManagement::LoadModel(24);
	GetEntityComponent<TransformComponent>(backpack).position.x = 5;
	
	AddEntityComponent<SkyboxComponent>(skybox);
	GetEntityComponent<SkyboxComponent>(skybox).cubemap = ResourceManagement::LoadCubemap(13, 6, 14, 4, 5, 3);
	
	AddEntityComponent<TransformComponent>(plane);
	AddEntityComponent<MeshComponent>(plane);
	GetEntityComponent<MeshComponent>(plane).model = ResourceManagement::LoadModel(SB_RESOURCE_MANIFEST_MESH_PLANE_ID);
	GetEntityComponent<MeshComponent>(plane).model->GetMeshes().at(0).SetTextureMap(txtr->id, txtr->type);
	GetEntityComponent<TransformComponent>(plane).position.y = -6;
	GetEntityComponent<TransformComponent>(plane).scale.x = 10;
	GetEntityComponent<TransformComponent>(plane).scale.z = 10;

	parent0 = AddEntity();
	parent1 = AddEntity();
	child0 = AddEntity();
	child1 = AddEntity();

	// Scene graph test

		AddEntityComponent<TransformComponent>(parent0);
		AddEntityComponent<TransformComponent>(parent1);
		AddEntityComponent<TransformComponent>(child0);
		AddEntityComponent<TransformComponent>(child1);
		AddEntityComponent<MeshComponent>(parent0);
		AddEntityComponent<MeshComponent>(parent1);
		AddEntityComponent<MeshComponent>(child0);
		AddEntityComponent<MeshComponent>(child1);
		GetEntityComponent<MeshComponent>(parent0).model = ResourceManagement::LoadModel(SB_RESOURCE_MANIFEST_MESH_CUBE_ID);
		GetEntityComponent<MeshComponent>(parent1).model = ResourceManagement::LoadModel(SB_RESOURCE_MANIFEST_MESH_CUBE_ID);
		GetEntityComponent<MeshComponent>(child0).model = ResourceManagement::LoadModel(SB_RESOURCE_MANIFEST_MESH_CUBE_ID);
		GetEntityComponent<MeshComponent>(child1).model = ResourceManagement::LoadModel(SB_RESOURCE_MANIFEST_MESH_CUBE_ID);

		GetEntityComponent<TransformComponent>(parent0).position = vec3(5);
		GetEntityComponent<TransformComponent>(child0).localPosition = vec3(0, -2, 0);
		GetEntityComponent<TransformComponent>(child0).localPosition = vec3(0, -3, 1);
		GetEntityComponent<TransformComponent>(parent1).position = vec3(-5);

		AddEntityComponent<HierarchyComponent>(parent0);
		GetEntityComponent<HierarchyComponent>(parent0).AddChild(child0);
		GetEntityComponent<HierarchyComponent>(parent0).AddChild(child1);
		// GetEntityComponent<HierarchyComponent>(parent0).SetParent(parent1);
	
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