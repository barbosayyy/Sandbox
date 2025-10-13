#include "Application.h"
#include "Game/IGame.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Core/Debug.h"

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

#ifdef SB_PROJECT_NAME
	sbEngine.GetRenderer().GetWindow()->SetWindowTitle(Sb::String(SB_PROJECT_NAME));
#endif

	std::unique_ptr<Sb::IGame> game = CreateGame(&sbEngine);
	game->Start();

	while(sbEngine.Validate() && !this->ShouldStop()) {
		sbEngine.Update();
		
		game->Update();
			
		sbEngine.Render();
		sbEngine.LateRender();
	}

	game->Stop();
	sbEngine.Stop();
}
