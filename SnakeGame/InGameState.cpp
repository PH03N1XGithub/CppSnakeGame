#include "InGameState.h"

#include <string>

#include "AppleObject.h"
#include "GameOverState.h"
#include "MainMenuState.h"
#include "SnakeObject.h"

InGameState::InGameState(SnakeGraphics* graphics, StateMachine* stateMachine,int levelIndex, bool bIsMultiplayerRef,bool bIsCoopWithAIRef) : graphics(graphics), sm(stateMachine), currentLevel(levelIndex), bIsMultiplayer(bIsMultiplayerRef), bIsCoopWithAI(bIsCoopWithAIRef)
{
    
}

InGameState::~InGameState()
{
    
}

bool InGameState::Init()
{
    for (int y = 0; y < graphics->GetNumRows(); y++)
    {
        for (int x = 0; x < graphics->GetNumColumns(); x++)
        {
            graphics->PlotTile(x, y, 0, {0,0,0}, {0,0,0}, L' ');
        }
    }
    graphics->Render();
    
    levels.clear();
    levels.push_back({
        L"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
    });
    levels.push_back({
        L"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        L"W......................................W",
        L"W...........WW.........................W",
        L"W......................................W",
        L"W......................................W",
        L"W..................WWW.................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W........WWWW..........................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W...........................WW.........W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W.........WWW..........................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"W......................................W",
        L"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
    });
    levels.push_back({
    L"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
    L"W......................................W",
    L"W...........WW...............WW........W",
    L"W......................................W",
    L"W......................................W",
    L"W..................WWW.................W",
    L"W......................................W",
    L"W............................WW........W",
    L"W......................................W",
    L"W......................................W",
    L"W......................................W",
    L"W......WWWW............................W",
    L"W......................................W",
    L"W......................................W",
    L"W......WWWW.................WW.........W",
    L"W......................................W",
    L"W......................................W",
    L"W.............................WW.......W",
    L"W......................................W",
    L"W.........WWW..........................W",
    L"W......................................W",
    L"W......................................W",
    L"W......................................W",
    L"W......................................W",
    L"W......................................W",
    L"W......................................W",
    L"W......................................W",
    L"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
    });
    
    world = new World(this);
    world->LoadLevel(levels[currentLevel]);
    
    snake = new SnakeObject(15, 15);
    snake->SetWorld(world);
    world->AddGameObject(snake);
    playerAgent = new PlayerAgent(EDirection::Right, VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT);
    std::vector<std::pair<int, int>> applePositions;
    int xPosForAI = 20;
    int yPosForAI = 15;

    if (currentLevel == 0)
    {
        xPosForAI = 10;
        yPosForAI = 10;
        applePositions = {
            {5, 5}, {8, 10}, {12, 6}, {20, 4}, {30, 15},
            {7, 20}, {25, 22}, {18, 17}, {34, 8}, {15, 13}
        };
    }
    else if (currentLevel == 1)
    {
        applePositions = {
            {3, 2}, {15, 3}, {25, 4}, {7, 10}, {17, 8},
            {30, 6}, {28, 12}, {20, 15}, {5, 18}, {35, 22}
        };
    }
    else if (currentLevel == 2)
    {
        applePositions = {
            {4, 3}, {10, 5}, {15, 8}, {22, 3}, {27, 7},
            {33, 11}, {6, 15}, {18, 13}, {25, 17}, {34, 21}
        };
    }
    if (bIsMultiplayer)
    {
        if (bIsCoopWithAI)
        {
            snake2 = new SnakeObject(xPosForAI, yPosForAI); 
            snake2->SetWorld(world);
            world->AddGameObject(snake2);
            simpleAIAgent = new SimpleAIAgent();
        }
        else
        {
            snake2 = new SnakeObject(25, 15);
            snake2->SetWorld(world);
            world->AddGameObject(snake2);
            playerAgent2 = new PlayerAgent(EDirection::Left, 'W', 'S', 'A', 'D');
        }
    }
    for (auto& pos : applePositions)
    {
        AppleObject* apple = new AppleObject(pos.first, pos.second);
        apple->SetWorld(world);
        world->AddGameObject(apple);
    }
    


    return true;
}

void InGameState::CleanUp()
{
    if (world)
    {
        delete world;
        world = nullptr;
    }
}

void InGameState::Update()
{
    if (snake && snake->bGameObjectDestroyed)
    {
        world->RemoveGameObject(snake);
        snake = nullptr;
        snake2 = nullptr;
        int lastScore = world->GetScore();
        delete world;
        world = nullptr;
        sm->ChangeState(new GameOverState(graphics, sm, lastScore));
        return;
    }
    if (bIsMultiplayer && snake2)
    {
        if(snake2->bGameObjectDestroyed)
        {
            world->RemoveGameObject(snake2);
            snake2 = nullptr;
            snake = nullptr;
            int lastScore = world->GetScore();
            delete world;
            world = nullptr;
            sm->ChangeState(new GameOverState(graphics, sm, lastScore));
            return;
        }
        if(playerAgent2)
        {
            playerAgent2->UpdateSnake(snake2);
        }
    }

    if (simpleAIAgent && snake2)
    {
        simpleAIAgent->UpdateSnake(snake2);
    }
    if (playerAgent && snake)
    {
        playerAgent->UpdateSnake(snake);
    }
    if (world && world->bLevelCompleted)
    {
        LoadNewLevel();
        return;
    }
    if (world)
    {
        world->Update();
    }
}

void InGameState::Render()
{
    if (world && graphics)
    {
        world->Render(graphics);
        graphics->Render();
    }
}

void InGameState::KeyDown(int key)
{
    if (key == VK_ESCAPE)
    {
        sm->ChangeState(nullptr);
    }
    if (playerAgent)
        playerAgent->OnKeyPressed(key);
    if (bIsMultiplayer && playerAgent2)
        playerAgent2->OnKeyPressed(key);
}

void InGameState::LoadNewLevel()
{
    if (currentLevel + 1 >= static_cast<int>(levels.size()))
    {
        sm->ChangeState(new MainMenuState(graphics, sm));
        return;
    }
    sm->ChangeState(new InGameState(graphics, sm, currentLevel + 1, bIsMultiplayer, bIsCoopWithAI));
}

