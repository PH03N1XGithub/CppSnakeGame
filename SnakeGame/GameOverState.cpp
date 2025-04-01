#include "GameOverState.h"

#include "InGameState.h"
#include "MainMenuState.h"

GameOverState::GameOverState(SnakeGraphics* graphics, StateMachine* stateMachine, int latestScoreRef) : graphics(graphics), m_stateMachine(stateMachine), latestScore(latestScoreRef)
{
}

GameOverState::~GameOverState()
{
}

bool GameOverState::Init()
{
    menuItems.push_back(L"Play again");
    menuItems.push_back(L"Main Menu");
    return true;
}

void GameOverState::CleanUp()
{
}

void GameOverState::Tick(float deltaTime)
{
}

void GameOverState::Render()
{
    for (int y = 0; y < graphics->GetNumRows(); y++)
    {
        for (int x = 0; x < graphics->GetNumColumns(); x++)
        {
            graphics->PlotTile(x, y, 0, {255,165,0}, {0,0,0}, L' ');
        }
    }
    
    int centerX = graphics->GetNumColumns() / 2;
    int msgY = 3;
    graphics->PlotText(centerX, msgY, 1, {255,165,0}, L"GAME OVER", {255, 0, 0}, SnakeGraphics::Center);
    
    int scoreY = msgY + 2;
    std::wstring scoreText = L"Score: " + std::to_wstring(latestScore);
    graphics->PlotText(centerX, scoreY, 1, {255,165,0}, scoreText.c_str(), {255,255,255}, SnakeGraphics::Center);
    
    int menuStartY = graphics->GetNumRows() - 3;
    for (size_t i = 0; i < menuItems.size(); i++)
    {
        Color menuColor = (i == selectedMenuIndex) ? Color(255,255,255) : Color(0,0,0);
        graphics->PlotText(centerX, static_cast<int>(i) + menuStartY, 1, {255,165,0}, menuItems[i].c_str(), menuColor, SnakeGraphics::Center);
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
            selectedMenuIndex = static_cast<int>(menuItems.size()) - 1;
        break;
    case VK_DOWN:
        selectedMenuIndex++;
        if (selectedMenuIndex >= static_cast<int>(menuItems.size()))
            selectedMenuIndex = 0;
        break;
    case VK_RETURN:
        if (menuItems[selectedMenuIndex] == L"Main Menu")
        {
            m_stateMachine->ChangeState(new MainMenuState(graphics, m_stateMachine));
        }
        else if (menuItems[selectedMenuIndex] == L"Play again")
        {
            m_stateMachine->ChangeState(new InGameState(graphics, m_stateMachine, 0,false,false));
        }
        break;
    case VK_ESCAPE:
        m_stateMachine->ChangeState(new MainMenuState(graphics, m_stateMachine));
        break;
    default:
        break;
    }
}
