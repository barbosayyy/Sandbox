
#include "Core/Base.h"
#include "Core/Config.h"
#include "Core/Debug.h"
#include "ECS/Components.h"
#include "ECS/Registry.h"
#include "Input/Input.h"
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
	Entity light0;
	Entity light1;
	Entity light2;

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
	AddEntityComponent<TransformComponent>(backpack);
	AddEntityComponent<MeshComponent>(backpack);
	AddEntityComponent<SkyboxComponent>(skybox);

	AddEntityComponent<LightComponent>(light0);

	GetEntityComponent<SkyboxComponent>(skybox).cubemap = ResourceManagement::LoadCubemap(13, 6, 14, 4, 5, 3);
	
	GetEntityComponent<MeshComponent>(backpack).model = ResourceManagement::LoadModel(24);

	GetEntityComponent<MeshComponent>(cube).model = ResourceManagement::LoadModel(SB_RESOURCE_MANIFEST_MESH_CUBE_ID);

	txtr = ResourceManagement::LoadTexture(15, TextureType::DIFFUSE);
	GetEntityComponent<MeshComponent>(cube).model->GetMeshes().at(0).SetTextureMap(txtr->id, txtr->type);

	GetEntityComponent<TransformComponent>(cube).pos = vec3(0, -2, -1);
	GetEntityComponent<TransformComponent>(cube).scale = vec3(0.5f);
	
	GetEntityComponent<TransformComponent>(backpack).pos.x = 5;

	GetEntityComponent<LightComponent>(light0).light->SetType(LightType::Point);

	SbGameUI::SetUIVisibility(false);

	Log::Info("SbGame: Started");
}

void Game::Update(){
	if(ping == true) {
		GetEntityComponent<TransformComponent>(cube).pos.x += 0.07f;
		if(GetEntityComponent<TransformComponent>(cube).pos.x >= 5) {
			ping = false;
		}
	}
	else {
		GetEntityComponent<TransformComponent>(cube).pos.x -= 0.07f;
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