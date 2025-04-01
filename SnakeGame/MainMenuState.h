#pragma once
#include "StateBase.h"
#include "StateMachine.h"
#include <vector>
#include <string>

#include "SnakeGraphics.h"

class MainMenuState: public StateBase
{
public:
    MainMenuState(SnakeGraphics* graphics, StateMachine* stateMachine);
    virtual ~MainMenuState();
    
    bool Init() override;
    void CleanUp() override;

    void Tick(float deltaTime) override;
    void Render() override;
    void KeyDown(int key) override;
private:
    SnakeGraphics* graphics = nullptr;
    StateMachine* m_stateMachine = nullptr;

    float deltatime;

    int selectedMenuIndex = 0;
    std::vector<std::wstring> menuItems;
    
};
