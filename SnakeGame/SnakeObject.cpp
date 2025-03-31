#include "SnakeObject.h"
#include "AppleObject.h"
#include "GameOverState.h"
#include "InGameState.h"
#include "StateMachine.h"
#include "World.h"


SnakeObject::SnakeObject(int x, int y) : lengthOfSnake(1)
{
    body.push_back({x, y});
}

SnakeObject::~SnakeObject()
{
    
}

void SnakeObject::Update()
{
    moveCounter++;
    if (moveCounter >= moveThreshold)
    {
        int headX = body.front().first;
        int headY = body.front().second;
        switch (direction)
        {
        case EDirection::Up:
            headY--;
            break;
        case EDirection::Down:
            headY++;
            break;
        case EDirection::Left:
            headX--;
            break;
        case EDirection::Right:
            headX++;
            break;
        }
        body.insert(body.begin(), {headX, headY});
        if (static_cast<int>(body.size()) > lengthOfSnake)
        {
            body.pop_back();
        }
        moveCounter = 0;
        if (body.size() > 1)
        {
            for (size_t i = 1; i < body.size(); i++)
            {
                if (body[0].first == body[i].first && body[0].second == body[i].second)
                {
                    OnCollisionEnter(nullptr);
                    break;
                }
            }
        }
    }
}

void SnakeObject::Render(SnakeGraphics* graphics)
{
    for (size_t i = 0; i < body.size(); i++)
    {
        wchar_t renderChar = (i == 0) ? L'O' : L'o';
        graphics->PlotTile(body[i].first, body[i].second, 1, {0, 0, 0}, {0, 0, 255}, renderChar);
    }
}

void SnakeObject::OnCollisionEnter(GameObject* other)
{
    AppleObject* apple = dynamic_cast<AppleObject*>(other);
    if (apple)
    {
        lengthOfSnake++;
        if (GetWorld())
        {
            GetWorld()->AddScore(1);
        }
    }
    else
    {
        bGameObjectDestroyed = true;
    }
}

void SnakeObject::SetPosition(int x, int y)
{
    body.clear();
    body.push_back({x, y});
    lengthOfSnake = 1;
}

void SnakeObject::SetDirection(EDirection dir)
{
    direction = dir;
}
