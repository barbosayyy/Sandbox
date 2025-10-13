#pragma once

#include "Game/IGame.h"
#include "Engine/IEngine.h"

class Game final : public Sb::IGame {
public:
    Game(Sb::IEngine& sbEngine);
    void Init() override final;
    void Start() override final;
    void Stop() override final;
    void Update() override final;
private:
    const Sb::IEngine& _sbEngine;
};
