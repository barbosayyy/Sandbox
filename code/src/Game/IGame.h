#pragma once

#include "Engine/IEngine.h"

namespace SbGame{

    // Engine interface for the game class. The game class should utilize this interface
    // in order to have isolated communication from the application

    class IGame{
    protected:
        IGame() = default;
    public:
        virtual ~IGame() = default;
        virtual void Init() = 0;
        virtual void Start() = 0;
        virtual void Stop() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
    };
}