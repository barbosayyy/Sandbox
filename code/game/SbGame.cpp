#include "SbGame.h"
#include "Core/Base.h"
#include "Core/Debug.h"
#include "Core/Types.h"
#include "Engine/Engine.h"
#include "Rendering/Primitives.h"
#include "Core/Utils.h"
#include "Rendering/Renderer.h"
#include "Resources/ShaderManager.h"
#include "stb_image/stb_image.h"
#include "Rendering/Camera.h"

// Game

using namespace SbEngine;
using namespace SbGame;

namespace SbGameGlobals{
	// Game Global variables 
}

using namespace SbGameGlobals;

Game::Game(IEngine& sbEngine) : _sbEngine(sbEngine){
}

void Game::Init(){
}

void Game::Start(){

	Logger::Print("SbGame: Finished start");
}

void Game::Update(){
	
}

void Game::Render(){
} 

void Game::Stop(){
}