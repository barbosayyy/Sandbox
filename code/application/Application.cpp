#include "Application.h"
#include "Game/IGame.h"
#include "Engine/Engine.h"
#include "Game/Game.h"

#include <memory>

using namespace SbApplication;

static std::unique_ptr<Sb::IGame> CreateGame(Sb::IEngine* sbEngine) {
	auto game = std::make_unique<Game>(*sbEngine);
	if(game) {
		game->Init();
	}
	return game;
}

void Application::Run() {
	Sb::Engine sbEngine;

	sbEngine.Start();

	std::unique_ptr<Sb::IGame> game = CreateGame(&sbEngine);
	game->Start();

	while(sbEngine.Validate() && !ShouldStop()) {
		sbEngine.Update();
		sbEngine.BeginNewFrame();

		game->Update();
		game->Render();

		sbEngine.Render();
	}

	game->Stop();
	sbEngine.Stop();
}
