#include "PlayerAgent.h"

PlayerAgent::PlayerAgent(EDirection initialDirection, int keyUp, int keyDown, int keyLeft, int keyRight) : pressedDirection(initialDirection), upKey(keyUp), downKey(keyDown), leftKey(keyLeft), rightKey(keyRight)
{
    
}

void PlayerAgent::UpdateSnake(SnakeObject* snake)
{
    snake->SetDirection(pressedDirection);
}

void PlayerAgent::OnKeyPressed(int key)
{
    if (key == upKey && pressedDirection != EDirection::Down)
        pressedDirection = EDirection::Up;
    else if (key == downKey && pressedDirection != EDirection::Up)
        pressedDirection = EDirection::Down;
    else if (key == leftKey && pressedDirection != EDirection::Right)
        pressedDirection = EDirection::Left;
    else if (key == rightKey && pressedDirection != EDirection::Left)
        pressedDirection = EDirection::Right;
}
