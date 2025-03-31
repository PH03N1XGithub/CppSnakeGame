#define NOMINMAX
#include "SimpleAIAgent.h"
#include <limits>

#include "AppleObject.h"
#include "World.h"

SimpleAIAgent::SimpleAIAgent()
{
}

void SimpleAIAgent::UpdateSnake(SnakeObject* snake)
{
    if (!snake || !snake->GetWorld())
        return;

    auto snakePos = std::make_pair(snake->GetX(), snake->GetY());
    auto applePos = FindNearestApplePosition(snake);

    int deltaX = applePos.first - snakePos.first;
    int deltaY = applePos.second - snakePos.second;

    if (std::abs(deltaX) > std::abs(deltaY))
    {
        if (deltaX > 0 && currentDirection != EDirection::Left)
            currentDirection = EDirection::Right;
        else if (deltaX < 0 && currentDirection != EDirection::Right)
            currentDirection = EDirection::Left;
    }
    else
    {
        if (deltaY > 0 && currentDirection != EDirection::Up)
            currentDirection = EDirection::Down;
        else if (deltaY < 0 && currentDirection != EDirection::Down)
            currentDirection = EDirection::Up;
    }

    snake->SetDirection(currentDirection);
}

std::pair<int, int> SimpleAIAgent::FindNearestApplePosition(SnakeObject* snake)
{
    World* world = snake->GetWorld();
    std::pair<int,int> nearestApple = {0,0};
    int closestDistance = std::numeric_limits<int>::max();

    for(auto obj : world->GetObjects())
    {
        AppleObject* apple = dynamic_cast<AppleObject*>(obj);
        if (apple)
        {
            int distance = std::abs(apple->GetX() - snake->GetX()) + std::abs(apple->GetY() - snake->GetY());
            if(distance < closestDistance)
            {
                closestDistance = distance;
                nearestApple = {apple->GetX(), apple->GetY()};
            }
        }
    }

    return nearestApple;
}
