#pragma once
#include "GameObject.h"

class AppleObject: public GameObject
{
public:
    AppleObject(int x, int y);
    virtual ~AppleObject();

    void Update() override;
    void Render(SnakeGraphics* graphics) override;
    void OnCollisionEnter(GameObject* other) override;

    int GetX() override {return posX;}
    int GetY() override {return posY;}
    void SetPosition(int x, int y) override;

private:
    int posX;
    int posY;
};
