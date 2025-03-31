#pragma once
#include <string>

#include "StateBase.h"
#include "SnakeGraphics.h"
#include "StateMachine.h"

class GameOverState : public StateBase
{
public:
    GameOverState(SnakeGraphics* graphics, StateMachine* stateMachine, int latestScoreRef);
    virtual ~GameOverState();

    bool Init() override;
    void CleanUp() override;

    void Update() override;
    void Render() override;
    void KeyDown(int key) override;
private:
    SnakeGraphics* graphics = nullptr;
    StateMachine* sm = nullptr;
    int latestScore = 0;
    int selectedMenuIndex = 0;
    std::vector<std::wstring> menuItems;
};
