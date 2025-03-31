#pragma once
#include "StateBase.h"

class StateMachine
{
    StateBase* activeState = nullptr;
public:
    StateBase* GetActiveState() const;
    void ChangeState(StateBase* newState);
    
};
