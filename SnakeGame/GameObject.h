#pragma once
#include "SnakeGraphics.h"

class World;

class GameObject
{
    World* world = nullptr;
public:

    virtual void Update() = 0;
    virtual void Render(SnakeGraphics* graphic) = 0;

    virtual int GetX() = 0;
    virtual int GetY() = 0;
    virtual void SetPosition(int x, int y) = 0;

    virtual void OnCollisionEnter(GameObject* other) = 0;
    void SetWorld(World* worldRef) { world = worldRef; }
    bool bGameObjectDestroyed = false;
    World* GetWorld() { return world; }
protected:

    
};
