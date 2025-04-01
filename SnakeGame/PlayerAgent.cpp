#include "PlayerAgent.h"

PlayerAgent::PlayerAgent(EDirection initialDirection, int keyUp, int keyDown, int keyLeft, int keyRight)
    :pressedDirection(initialDirection)
    , m_Key{keyUp, keyDown, keyLeft, keyRight}
{
    
}

void PlayerAgent::UpdateSnake(SnakeObject* snake)
{
    snake->SetDirection(pressedDirection);
}

void PlayerAgent::OnKeyPressed(int key)
{
    if (key == m_Key.up && pressedDirection != EDirection::Down)
        pressedDirection = EDirection::Up;
    else if (key == m_Key.down && pressedDirection != EDirection::Up)
        pressedDirection = EDirection::Down;
    else if (key == m_Key.left && pressedDirection != EDirection::Right)
        pressedDirection = EDirection::Left;
    else if (key == m_Key.righ && pressedDirection != EDirection::Left)
        pressedDirection = EDirection::Right;
}
