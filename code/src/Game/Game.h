#pragma once

#include "Game/IGame.h"
#include "Engine/IEngine.h"

class Game : public Sb::IGame {
public:
    Game(Sb::IEngine& sbEngine);
    void Init() override;
    void Start() override;
    void Stop() override;
    void Update() override;
    void Render() override;
private:
    const Sb::IEngine& _sbEngine;
};
