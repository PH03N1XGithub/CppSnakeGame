// Game.h
#pragma once

#include "StateMachine.h"
#include "SnakeGraphics.h"

class Game
{
public:
    Game() = default;
    ~Game();
    void Run();


private:
    SnakeGraphics* graphics = nullptr;
    StateMachine stateMachine;
private:
    
    bool Init();
    void Tick(float deltaTime) const;
    void Render() const;
    void KeyDownCallback(int key) const;
};


