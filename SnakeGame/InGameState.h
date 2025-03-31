#pragma once
#include "PlayerAgent.h"
#include "SimpleAIAgent.h"
#include "SnakeGraphics.h"
#include "StateBase.h"
#include "StateMachine.h"
#include "World.h"

class InGameState: public StateBase
{
public:
    InGameState(SnakeGraphics* graphics, StateMachine* stateMachine, int levelIndex, bool bIsMultiplayerRef, bool bIsCoopWithAIRef);
    virtual ~InGameState();

    bool Init() override;
    void CleanUp() override;

    void Update() override;
    void Render() override;
    void KeyDown(int key) override;
    void LoadNewLevel();

private:
    SnakeGraphics* graphics = nullptr;
    StateMachine* sm = nullptr;
    int exampleCounter = 0;
    World* world = nullptr;
    PlayerAgent* playerAgent = nullptr;
    PlayerAgent* playerAgent2 = nullptr;
    SimpleAIAgent* simpleAIAgent = nullptr;
    SnakeObject* snake = nullptr;
    SnakeObject* snake2 = nullptr;
    bool bIsMultiplayer = false;
    bool bIsCoopWithAI = false;
    
    std::vector<std::vector<std::wstring>> levels;
    int currentLevel = 0;
    const int scoreThresholdForLevelTransition = 10;
};
