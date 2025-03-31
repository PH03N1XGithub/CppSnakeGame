#include "AppleObject.h"

#include "SnakeObject.h"
#include "World.h"

AppleObject::AppleObject(int x, int y) : posX(x), posY(y)
{
    
}

AppleObject::~AppleObject()
{
    
}

void AppleObject::Update()
{
    
}

void AppleObject::Render(SnakeGraphics* graphics)
{
    graphics->PlotTile(posX, posY, 1, {255, 0, 0}, {0, 0, 0}, L' ');
}

void AppleObject::OnCollisionEnter(GameObject* other)
{
    SnakeObject* snake = dynamic_cast<SnakeObject*>(other);
    if (other == snake)
    {
        GetWorld()->RemoveGameObject(this);
    }
}

void AppleObject::SetPosition(int x, int y)
{
    posX = x;
    posY = y;
}
