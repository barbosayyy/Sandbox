#pragma once

#include "Game/IGame.h"
#include "Engine/IEngine.h"

namespace SbGame {
    class Game : public SbGame::IGame{
    public:
        Game(SbEngine::IEngine& sbEngine);
        void Init() override;
        void Start() override;
        void Stop() override;
        void Update() override;
        void Render() override;
    private:
        const SbEngine::IEngine& _sbEngine;
    };
}