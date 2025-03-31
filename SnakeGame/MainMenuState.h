#pragma once
#include "StateBase.h"
#include "SnakeGraphics.h"
#include "StateMachine.h"
#include <vector>
#include <string>

class MainMenuState: public StateBase
{
public:
    MainMenuState(SnakeGraphics* graphics, StateMachine* stateMachine);
    virtual ~MainMenuState();
    
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
    bool menuRunning = true;
    
};
