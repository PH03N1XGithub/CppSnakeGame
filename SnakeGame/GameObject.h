#pragma once
#include "SnakeGraphics.h"

class GameObject
{
private:
    friend class World;
    friend class InGameState;
    World* m_World = nullptr;
    virtual void Update() = 0;
    virtual void Render(SnakeGraphics* graphic) = 0;
    
public:
    
    virtual ~GameObject() = default;
    virtual int GetX() = 0;
    virtual int GetY() = 0;
    World* GetWorld() const { return m_World; }

protected:
    
    virtual void SetPosition(int x, int y) = 0;
    void SetWorld(World* worldRef) { m_World = worldRef; }
    bool bGameObjectDestroyed = false;
    virtual void OnCollisionEnter(GameObject* other) = 0;

};
