#pragma once
#include <string>

#include "SnakeGraphics.h"
#include "StateBase.h"
#include "StateMachine.h"

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
    void Update() override;
    void Render() override;
    void KeyDown(int key) override;
private:
    SnakeGraphics* graphics = nullptr;
    StateMachine* sm = nullptr;
    int selectedMenuIndex = 0;
    std::vector<std::wstring> menuItems;
};
