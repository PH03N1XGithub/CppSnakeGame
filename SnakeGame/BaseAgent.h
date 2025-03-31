#pragma once
#include "SnakeObject.h"

class BaseAgent
{
public:
    virtual void UpdateSnake(SnakeObject* snake) = 0;
};
