#include "GameOverState.h"

#include "InGameState.h"
#include "MainMenuState.h"

GameOverState::GameOverState(SnakeGraphics* graphics, StateMachine* stateMachine, int latestScoreRef) : graphics(graphics), sm(stateMachine), latestScore(latestScoreRef)
{
}

GameOverState::~GameOverState()
{
}

bool GameOverState::Init()
{
    menuItems.push_back(L"Press Enter to play again");
    menuItems.push_back(L"Main Menu");
    return true;
}

void GameOverState::CleanUp()
{
}

void GameOverState::Update()
{
}

void GameOverState::Render()
{
    for (int y = 0; y < graphics->GetNumRows(); y++)
    {
        for (int x = 0; x < graphics->GetNumColumns(); x++)
        {
            graphics->PlotTile(x, y, 0, {0,0,0}, {0,0,0}, L' ');
        }
    }
    
    int centerX = graphics->GetNumColumns() / 2;
    int msgY = 3;
    graphics->PlotText(centerX, msgY, 1, {0,0,0}, L"GAME OVER", {255, 0, 0}, SnakeGraphics::Center);
    
    int scoreY = msgY + 2;
    std::wstring scoreText = L"Score: " + std::to_wstring(latestScore);
    graphics->PlotText(centerX, scoreY, 1, {0,0,0}, scoreText.c_str(), {255,255,255}, SnakeGraphics::Center);
    
    int menuStartY = graphics->GetNumRows() - 3;
    for (size_t i = 0; i < menuItems.size(); i++)
    {
        Color menuColor = (i == selectedMenuIndex) ? Color(255,255,255) : Color(128,128,128);
        graphics->PlotText(centerX, menuStartY + i, 1, {0,0,0}, menuItems[i].c_str(), menuColor, SnakeGraphics::Center);
    }
    
    graphics->Render();
}

void GameOverState::KeyDown(int key)
{
    switch (key)
    {
    case VK_UP:
        selectedMenuIndex--;
        if (selectedMenuIndex < 0)
            selectedMenuIndex = (int)menuItems.size() - 1;
        break;
    case VK_DOWN:
        selectedMenuIndex++;
        if (selectedMenuIndex >= (int)menuItems.size())
            selectedMenuIndex = 0;
        break;
    case VK_RETURN:
        if (menuItems[selectedMenuIndex] == L"Main Menu")
        {
            sm->ChangeState(new MainMenuState(graphics, sm));
        }
        else if (menuItems[selectedMenuIndex] == L"Press Enter to play again")
        {
            sm->ChangeState(new InGameState(graphics, sm, 0,false,false));
        }
        break;
    case VK_ESCAPE:
        sm->ChangeState(new MainMenuState(graphics, sm));
        break;
    default:
        break;
    }
}
