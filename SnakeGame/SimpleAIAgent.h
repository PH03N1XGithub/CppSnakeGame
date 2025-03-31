#pragma once
#include "BaseAgent.h"


class SimpleAIAgent : public BaseAgent
{
public:
    SimpleAIAgent();
    virtual void UpdateSnake(SnakeObject* snake) override;
private:
    EDirection currentDirection = EDirection::Right;
    std::pair<int,int> FindNearestApplePosition(SnakeObject* snake);
    
};
