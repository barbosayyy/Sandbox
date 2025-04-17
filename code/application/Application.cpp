#include "Application.h"
#include "Core/Base.h"
#include "Core/Debug.h"
#include "Game/IGame.h"
#include "Engine/Engine.h"
#include "SbGame.h"

#include <memory>

using namespace SbApplication;
using namespace SbEngine;

static std::unique_ptr<SbGame::IGame> CreateGame(IEngine* sbEngine){
    auto game = std::make_unique<SbGame::Game>(*sbEngine);
    if(game){
        game->Init();
    }
    return game;
}

void Application::Run(){
    Engine sbEngine;

    sbEngine.Start();

    std::unique_ptr<SbGame::IGame> game = CreateGame(&sbEngine);
    game->Start();
    
    while(sbEngine.Validate() && !ShouldStop()){
        sbEngine.Update();
        sbEngine.BeginNewFrame();

        game->Update();
        game->Render();

        sbEngine.Render();
    }

    game->Stop();
    sbEngine.Stop();
}