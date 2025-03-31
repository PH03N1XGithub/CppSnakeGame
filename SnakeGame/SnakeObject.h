#pragma once
#include "GameObject.h"

enum class EDirection
{
    Up,
    Down,
    Left,
    Right
};

class SnakeObject : public GameObject
{
public:
    SnakeObject(int x, int y);
    ~SnakeObject();

    void Update() override;
    void Render(SnakeGraphics* graphics) override;

    void OnCollisionEnter(GameObject* other) override;

    int GetX() override { return body.empty() ? 0 : body.front().first; }
    int GetY() override { return body.empty() ? 0 : body.front().second; }
    void SetPosition(int x, int y) override;
    void SetDirection(EDirection dir);
    int GetLength() const { return lengthOfSnake; }
private:
    std::vector<std::pair<int,int>> body;
    int posX;
    int posY;
    EDirection direction = EDirection::Right;
    int moveCounter = 0;
    int moveThreshold = 5;
    int lengthOfSnake = 1;
};
