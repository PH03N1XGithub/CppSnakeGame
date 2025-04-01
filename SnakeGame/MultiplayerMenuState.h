#pragma once
#include <string>

#include "StateBase.h"
#include "StateMachine.h"
#include "SnakeGraphics.h"

enum class EMultiplayerMode
{
    Coop,
    Battle
};

class MultiplayerMenuState : public StateBase
{
public:
    MultiplayerMenuState(SnakeGraphics* graphics, StateMachine* stateMachine);
    virtual ~MultiplayerMenuState();

    bool Init() override;
    void CleanUp() override;
    void Tick(float deltaTime) override;
    void Render() override;
    void KeyDown(int key) override;
private:
    SnakeGraphics* graphics = nullptr;
    StateMachine* m_stateMachine = nullptr;
    int selectedMenuIndex = 0;
    std::vector<std::wstring> menuItems;
};
