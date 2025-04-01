#pragma once
#include "PlayerAgent.h"
#include "SimpleAIAgent.h"
#include "StateBase.h"
#include "StateMachine.h"
#include "World.h"
#include "GameObject.h"

class InGameState: public StateBase
{
public:
    friend class GameObject;
    InGameState(SnakeGraphics* graphics, StateMachine* stateMachine, int levelIndex, bool bIsMultiplayerRef, bool bIsCoopWithAIRef);
    virtual ~InGameState();

    bool Init() override;
    void CleanUp() override;

    void Tick(float deltaTime) override;
    void Render() override;
    void KeyDown(int key) override;
    void LoadNewLevel() const;

private:
    
    SnakeGraphics* graphics = nullptr;
    StateMachine* m_stateMachine = nullptr;
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
};
