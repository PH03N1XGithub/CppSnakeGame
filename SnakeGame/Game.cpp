
#include "Game.h"
#include "SnakeInput.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <Windows.h>
#include "MainMenuState.h"

Game::Game()
{
}

Game::~Game()
{
    SnakeInput::CleanUp();
    if (graphics) {
        delete graphics;
        graphics = nullptr;
    }
}

bool Game::Init()
{
    graphics = new SnakeGraphics(1024, 720, 40, 30);
    if (!graphics->Init()) {
        std::cerr << "SnakeGraphics init failed!\n";
        return false;
    }
    
    if (!SnakeInput::Init(graphics)) {
        std::cerr << "SnakeInput init failed!\n";
        return false;
    }
    
    SnakeInput::AddKeyDownCallback(std::bind(&Game::KeyDownCallback, this, std::placeholders::_1));
    
    stateMachine.ChangeState(new MainMenuState(graphics, &stateMachine));

    running = true;
    return true;
}

void Game::Run()
{
    while (running)
    {
        running = graphics->UpdateWindowMessages();
        
        StateBase* current = stateMachine.GetActiveState();
        if (!current)
        {
            running = false;
        }
        else
        {
            current->Update();
            StateBase* newState = stateMachine.GetActiveState();
            if (newState != current)
            {
                current = newState;
                if (!current)
                {
                    running = false;
                }
                else
                {
                    current->Render();
                }
            }
            else
            {
                current->Render();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(frameTimeMs));
    }
}

void Game::KeyDownCallback(int key)
{
    StateBase* current = stateMachine.GetActiveState();
    if (current)
    {
        current->KeyDown(key);
    }
    else
    {
        running = false;
    }
}
