#include "InGameState.h"

#include <ctime>
#include <string>

#include "AppleObject.h"
#include "GameOverState.h"
#include "MainMenuState.h"
#include "SnakeObject.h"

InGameState::InGameState(SnakeGraphics* graphics, StateMachine* stateMachine,int levelIndex, bool bIsMultiplayerRef,bool bIsCoopWithAIRef) : graphics(graphics), m_stateMachine(stateMachine), currentLevel(levelIndex), bIsMultiplayer(bIsMultiplayerRef), bIsCoopWithAI(bIsCoopWithAIRef)
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
        L"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
    });
    levels.push_back({
        L"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        L"W..........................................................W",
        L"W...........WW...............................WWWWWWWW......W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..................WWW....................WWWWWWWW.........W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W........WWWW..............................................W",
        L"W.............................................W..W..........W",
        L"W.............................................W..W.........W",
        L"W.............................................W..W.........W",
        L"W...........................WW................W..W.........W",
        L"W.............................................W..W.........W",
        L"W.............................................W..W.........W",
        L"W.............................................W..W.........W",
        L"W.............................................W..W.........W",
        L"W.............................................W..W.........W",
        L"W.............................................W..W.........W",
        L"W.............................................W..W.........W",
        L"W.........WWW.................................W..W.........W",
        L"W.............................................W..W.........W",
        L"W.............................................W..W.........W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"W...........................................WWWWWW.........W",
        L"W..........................................................W",
        L"W..........................................................W",
        L"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
    });
    levels.push_back({
    L"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
    L"W..........................................................W",
    L"W...........WW...............WW............................W",
    L"W................................................wwww......W",
    L"W..........................................................W",
    L"W..................WWW.....................................W",
    L"W................................................wwww......W",
    L"W............................WW............................W",
    L"W..........................................................W",
    L"W..........................................................W",
    L"W.....................................................ww...W",
    L"W..........................................................W",
    L"W......WWWW...................................wwww.........W",
    L"W..........................................................W",
    L"W..................................................wwww....W",
    L"W......WWWW.................WW.............................W",
    L"W....................................................ww....W",
    L"W..........................................................W",
    L"W.............................WW.....................ww....W",
    L"W..........................................................W",
    L"W.........WWW..............................................W",
    L"W.........WWW..............................................W",
    L"W..........................................................W",
    L"W............................................wwwwwww.......W",
    L"W..........................................................W",
    L"W..........................................................W",
    L"W..........................................................W",
    L"W..........................................................W",
    L"W..............................................wwwww.......W",
    L"W..........................................................W",
    L"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
    });
    
    world = new World(this);
    world->LoadLevel(levels[currentLevel]);
    
    snake = new SnakeObject(15, 15);
    snake->SetWorld(world);
    world->AddGameObject(snake);
    playerAgent = new PlayerAgent(EDirection::Right, VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT);
    int xPosForAI = 20;
    int yPosForAI = 15;

    
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

    const std::vector<std::wstring>& levelData = levels[currentLevel];
    for (int y = 0; y < static_cast<int>(levelData.size()); y++)
    {
        for (int x = 0; x < static_cast<int>(levelData[y].size()); x++)
        {
            const wchar_t tile_char = levelData[y][x];
            if (tile_char != L'W' && rand() % 120 == 0)
            {

                const auto apple = new AppleObject(x, y);  
                apple->SetWorld(world);  
                world->AddGameObject(apple);
                    
                graphics->PlotTile(x, y, 0,{15, 0, 15},{0, 0, 0},L' ');
            }
        }
    }
    return true;
}

void InGameState::CleanUp()
{
    delete world;
}

void InGameState::Tick(float deltaTime)
{
    if (snake && snake->bGameObjectDestroyed)
    {
        world->RemoveGameObject(snake);
        snake = nullptr;
        snake2 = nullptr;
        int lastScore = world->GetScore();
        m_stateMachine->ChangeState(new GameOverState(graphics, m_stateMachine, lastScore));
        return;
    }
    if (bIsMultiplayer && snake2)
    {
        if(snake2->bGameObjectDestroyed)
        {
            world->RemoveGameObject(snake2);
            snake2 = nullptr;
            snake = nullptr;
            const int lastScore = world->GetScore();
            //delete world;
            m_stateMachine->ChangeState(new GameOverState(graphics, m_stateMachine, lastScore));
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

void InGameState::KeyDown(const int key)
{
    if (key == VK_ESCAPE)
    {
        m_stateMachine->ChangeState(new MainMenuState(graphics, m_stateMachine));
    }if (key == 'Q')
    {
        LoadNewLevel();
    }
    if (playerAgent)
        playerAgent->OnKeyPressed(key);
    if (bIsMultiplayer && playerAgent2)
        playerAgent2->OnKeyPressed(key);
}

void InGameState::LoadNewLevel() const
{
    if (currentLevel + 1 >= static_cast<int>(levels.size()))
    {
        m_stateMachine->ChangeState(new MainMenuState(graphics, m_stateMachine));
        return;
    }
    m_stateMachine->ChangeState(new InGameState(graphics, m_stateMachine, currentLevel + 1, bIsMultiplayer, bIsCoopWithAI));
}

