#pragma once
#include "GameObject.h"
#include "SnakeGraphics.h"
#include <vector>
#include <string>

#include "StateBase.h"

class World
{
public:
    World(StateBase* stateBaseRef);
    ~World();

    bool LoadLevel(const std::vector<std::wstring>& levelData);

    void Update();
    void Render(SnakeGraphics* graphics);
    
    void AddGameObject(GameObject* obj);
    void RemoveGameObject(GameObject* obj);

    void AddScore(int amountOfScore);
    int GetScore() const { return score; }
    bool bLevelCompleted = false;
    std::vector<GameObject*> GetObjects() const { return objects; }


private:
    std::vector<std::wstring> mapData;
    std::vector<GameObject*> objects;
    StateBase* stateBase = nullptr;
    int score = 0;
};
