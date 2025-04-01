#pragma once
#include "BaseAgent.h"

class PlayerAgent : public BaseAgent
{
public:
    PlayerAgent(EDirection initialDirection, int keyUp, int keyDown, int keyLeft, int keyRight);
    void UpdateSnake(SnakeObject* snake) override;
    void OnKeyPressed(int key);
private:
    EDirection pressedDirection = EDirection::Right;
    struct Key
    {
        int up, down, left, righ;
    }m_Key;
    
};
