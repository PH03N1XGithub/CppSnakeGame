﻿#include "StateMachine.h"

StateBase* StateMachine::GetActiveState() const
{
    return activeState;
}

void StateMachine::ChangeState(StateBase* newState)
{
    if (activeState)
    {
        activeState->CleanUp();
        activeState = nullptr;
    }

    activeState = newState;

    if (activeState)
    {
        activeState->Init();
    }
}
