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
    ~SnakeObject() override;

    int GetX() override { return body.empty() ? 0 : body.front().first; }
    int GetY() override { return body.empty() ? 0 : body.front().second; }
    int GetLength() const { return lengthOfSnake; }
    void SetDirection(EDirection dir);
    
private:
    
    void Update() override;
    void Render(SnakeGraphics* graphics) override;

    void OnCollisionEnter(GameObject* other) override;
    void SetPosition(int x, int y) override;

    
    std::vector<std::pair<int,int>> body;
    EDirection direction = EDirection::Right;
    float moveCounter = 0;
    float moveThreshold = 1;
    int lengthOfSnake = 1;
};
