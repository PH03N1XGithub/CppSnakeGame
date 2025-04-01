#include "MultiplayerMenuState.h"

#include "InGameState.h"
#include "MainMenuState.h"

MultiplayerMenuState::MultiplayerMenuState(SnakeGraphics* graphics, StateMachine* stateMachine) : graphics(graphics), m_stateMachine(stateMachine)
{
}

MultiplayerMenuState::~MultiplayerMenuState()
{
}

bool MultiplayerMenuState::Init()
{
    menuItems.push_back(L"Co-op Mode");
    menuItems.push_back(L"Co-op Mode with AI");
    menuItems.push_back(L"Battle Mode");
    menuItems.push_back(L"Back to Main Menu");
    for (int y = 0; y < graphics->GetNumRows(); y++)
    {
        for (int x = 0; x < graphics->GetNumColumns(); x++)
        {
            graphics->PlotTile(x, y, 0, {0,0,0}, {0,0,0}, L' ');
        }
    }
    graphics->Render();
    return true;
}

void MultiplayerMenuState::CleanUp()
{
}

void MultiplayerMenuState::Tick(float deltaTime)
{
}

void MultiplayerMenuState::Render()
{
    int centerX = graphics->GetNumColumns() / 2;
    int centerY = graphics->GetNumRows() / 2;

    for (int i = 0; i < static_cast<int>(menuItems.size()); i++)
    {
        Color colorForMenu = (i == selectedMenuIndex) ? Color(255, 255, 255) : Color(128, 128, 128);

        graphics->PlotText(
            centerX,
            centerY + i,
            0,
            {0, 0, 0},
            menuItems[i].c_str(),
            colorForMenu,
            SnakeGraphics::Center
        );
    }

    graphics->Render();
}

void MultiplayerMenuState::KeyDown(int key)
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
        if (menuItems[selectedMenuIndex] == L"Co-op Mode")
        {
            m_stateMachine->ChangeState(new InGameState(graphics, m_stateMachine, 0, true, false));
        }
        else if (menuItems[selectedMenuIndex] == L"Co-op Mode with AI")
        {
            m_stateMachine->ChangeState(new InGameState(graphics, m_stateMachine, 0, true, true));
        }
        else if (menuItems[selectedMenuIndex] == L"Battle Mode")
        {
            m_stateMachine->ChangeState(new InGameState(graphics, m_stateMachine, 0, true,false));
        }
        else if (menuItems[selectedMenuIndex] == L"Back to Main Menu")
        {
            m_stateMachine->ChangeState(new MainMenuState(graphics, m_stateMachine));
        }
        break;

    case VK_ESCAPE:
        m_stateMachine->ChangeState(new MainMenuState(graphics, m_stateMachine));
        break;

    default:
        break;
    }
}
