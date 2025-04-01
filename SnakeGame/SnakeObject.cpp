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

static struct Position
{
    int x;
    int y;
}SnakePosition;

void SnakeObject::Update()
{
    moveCounter+= 0.06f;
    if (moveCounter >= moveThreshold)
    {
        
        SnakePosition.x = body.front().first;
        SnakePosition.y = body.front().second;
        switch (direction)
        {
        case EDirection::Up:
            SnakePosition.y--;
            break;
        case EDirection::Down:
            SnakePosition.y++;
            break;
        case EDirection::Left:
            SnakePosition.x--;
            break;
        case EDirection::Right:
            SnakePosition.x++;
            break;
        }
        body.insert(body.begin(), {SnakePosition.x, SnakePosition.y});
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
        int renderChar = static_cast<int>(255 * (1.0 - static_cast<float>(i) / 10.0));
        graphics->PlotTile(body[i].first, body[i].second, 1, {0, 255, renderChar},
            {255, 165, 0}, L':');
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
