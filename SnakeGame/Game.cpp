
#include "Game.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <Windows.h>
#include "MainMenuState.h"
#include "SnakeInput.h"
#include "stdafx.h"

bool Game::Init()
{
    graphics = new SnakeGraphics(1280, 720, WORLD_WIDTH, WORLD_HEIGHT);
    
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
    
    return true;
}

void Game::Run()
{
    if (!Init()) {
        std::cerr << "GAME START FAILED!"<< '\n';
        return;
    }
    auto last_time = std::chrono::high_resolution_clock::now();
    while (graphics->UpdateWindowMessages())
    {
        auto current_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = current_time - last_time;
        double delta_time = elapsed.count();
        
        long time_left = static_cast<long>(1000.0 / FPS - delta_time);
        
        if (time_left > 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(time_left));
        }
		
        last_time = std::chrono::high_resolution_clock::now();

        std::cout << "Delta Time: " << delta_time << " ms (Target: " << 1000.0 / FPS << " ms)\n";

        const float deltaTime = static_cast<float>(delta_time);
        
        Tick(deltaTime);
        Render();
        
    }
}

void Game::Tick(float deltaTime) const
{
    stateMachine.GetActiveState()->Tick(deltaTime);
}

void Game::Render() const
{
    stateMachine.GetActiveState()->Render();
}

void Game::KeyDownCallback(int key) const
{
    std::cout << "Key down:" << key << '\n';
    stateMachine.GetActiveState()->KeyDown(key);
}

Game::~Game()
{
    SnakeInput::CleanUp();
    if (graphics) {
        delete graphics;
        graphics = nullptr;
    }
}

