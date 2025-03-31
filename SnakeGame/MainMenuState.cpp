#include "MainMenuState.h"
#include <iostream>

#include "InGameState.h"
#include "MultiplayerMenuState.h"
#include "StateMachine.h"

MainMenuState::MainMenuState(SnakeGraphics* graphics, StateMachine* stateMachine) : graphics(graphics), sm(stateMachine)
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
    menuItems.push_back(L"Start");
    menuItems.push_back(L"Multiplayer"); 
    menuItems.push_back(L"Exit");
    return true;
}

void MainMenuState::CleanUp()
{
}

void MainMenuState::Update()
{
}

void MainMenuState::Render()
{
    int centerX = graphics->GetNumColumns() / 2;
    int centerY = graphics->GetNumRows() / 2;

    for (int i = 0; i < (int)menuItems.size(); i++)
    {
        Color colorForMenu = (i == selectedMenuIndex) ? Color(255, 255, 255) : Color(128, 128, 128);

        int xPos = centerX;
        int yPos = centerY + i;

        graphics->PlotText(
            xPos,
            yPos,
            0,
            {0, 0, 0},
            menuItems[i].c_str(),
            colorForMenu,
            SnakeGraphics::Center
        );
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
            selectedMenuIndex = (int)menuItems.size() - 1;
        }
        break;

    case VK_DOWN:
        selectedMenuIndex++;
        if (selectedMenuIndex >= (int)menuItems.size()) {
            selectedMenuIndex = 0;
        }
        break;

    case VK_RETURN:
        if (menuItems[selectedMenuIndex] == L"Start")
        {
            sm->ChangeState(new InGameState(graphics, sm,0,false,false));
        }
        else if (menuItems[selectedMenuIndex] == L"Multiplayer")
        {
            sm->ChangeState(new MultiplayerMenuState(graphics, sm)); 
        }
        else if (menuItems[selectedMenuIndex] == L"Exit")
        {
            std::wcout << L"Quit selected\n";
            exit(0);
        }
        break;

    case VK_ESCAPE:
            sm->ChangeState(nullptr);
        break;

    default:
        break;
    }
}

