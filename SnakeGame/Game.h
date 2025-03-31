// Game.h
#pragma once

#include "SnakeGraphics.h"
#include "StateMachine.h"

class Game
{
public:
    Game();
    ~Game();

    bool Init();
    void Run();

private:
    void KeyDownCallback(int key);
    
    SnakeGraphics* graphics = nullptr;
    bool running = true;
    StateMachine stateMachine;
    const int frameTimeMs = 16;
};
