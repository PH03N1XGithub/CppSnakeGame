#include "MainMenuState.h"
#include <iostream>

#include "InGameState.h"
#include "MultiplayerMenuState.h"
#include "StateMachine.h"
#include "stdafx.h"

MainMenuState::MainMenuState(SnakeGraphics* graphics, StateMachine* stateMachine) : graphics(graphics), m_stateMachine(stateMachine)
{

}

MainMenuState::~MainMenuState()
{
    
}
bool MainMenuState::Init()
{
    for (int y = 0; y < graphics->GetNumRows(); y++)
    {
        for (int x = 0; x < graphics->GetNumColumns(); x++)
        {
            graphics->PlotTile(x, y, 0, {0,0,0}, {0,0,0}, L' ');
        }
    }
    graphics->Render();
    menuItems.push_back(L"Play");
    menuItems.push_back(L"CO-OP"); 
    menuItems.push_back(L"Exit");
    return true;
}

void MainMenuState::CleanUp()
{
}

void MainMenuState::Tick(float deltaTime)
{
    deltatime = deltaTime;
}

void MainMenuState::Render()
{
    for (int i = 0; i < static_cast<int>(menuItems.size()); i++)
    {
        Color colorForMenu = (i == selectedMenuIndex) ? Color(255, 255, 255) : Color(128, 128, 128);
        int a = 255;
        graphics->PlotText(WORLD_WIDTH / 2,WORLD_HEIGHT / 2 + i,0,{0, 0, 0},
            menuItems[i].c_str(),colorForMenu,SnakeGraphics::Center);
    }
    
    const float waveSpeed = 0.2f;  
    const float frequency = 0.04f;  
    for (int y = 0; y < WORLD_HEIGHT; y++) {
        for (int x = 0; x < WORLD_WIDTH; x++) {

            float waveValue = sinf((x + deltatime * waveSpeed) * frequency);
            
            int red = (int)(127 * (waveValue + 1));  
            int green = (int)(127 * (waveValue + 1));
            int blue = (int)(255 * (1 - waveValue));
            
            graphics->PlotTile(x, y, 0, {red, green, blue}, {0, 0, 0}, L' '); 
        }
    }
    graphics->Render();
}

void MainMenuState::KeyDown(int key)
{
    switch (key)
    {
    case VK_UP:
        selectedMenuIndex--;
        if (selectedMenuIndex < 0) {
            selectedMenuIndex = static_cast<int>(menuItems.size()) - 1;
        }
        break;

    case VK_DOWN:
        selectedMenuIndex++;
        if (selectedMenuIndex >= static_cast<int>(menuItems.size())) {
            selectedMenuIndex = 0;
        }
        break;

    case VK_RETURN:
        if (menuItems[selectedMenuIndex] == L"Play")
        {
            m_stateMachine->ChangeState(new InGameState(graphics, m_stateMachine,0,false,false));
        }
        else if (menuItems[selectedMenuIndex] == L"CO-OP")
        {
            m_stateMachine->ChangeState(new MultiplayerMenuState(graphics, m_stateMachine)); 
        }
        else if (menuItems[selectedMenuIndex] == L"Exit")
        {
            std::wcout << L"Quit\n";
            exit(0);
        }
        break;

    case VK_ESCAPE:
            exit(0);
        break;

    default:
        break;
    }
}

