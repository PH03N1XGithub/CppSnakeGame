#pragma once
#include <string>

#include "StateBase.h"
#include "StateMachine.h"
#include "SnakeGraphics.h"

class GameOverState : public StateBase
{
public:
    GameOverState(SnakeGraphics* graphics, StateMachine* stateMachine, int latestScoreRef);
    virtual ~GameOverState();

    bool Init() override;
    void CleanUp() override;

    void Tick(float deltaTime) override;
    void Render() override;
    void KeyDown(int key) override;
private:
    SnakeGraphics* graphics = nullptr;
    StateMachine* m_stateMachine = nullptr;
    int latestScore = 0;
    int selectedMenuIndex = 0;
    std::vector<std::wstring> menuItems;
};
