
#include "World.h"
#include <algorithm>

#include "AppleObject.h"


World::World(StateBase* stateBaseRef) : stateBase(stateBaseRef)
{
}

World::~World()
{
    for (auto obj : objects)
    {
        delete obj;
    }
    objects.clear();
}

bool World::LoadLevel(const std::vector<std::wstring>& levelData)
{
    mapData = levelData;
    return true;
}

void World::Update()
{
    for (auto obj : objects)
    {
        obj->Update();
    }
    
    for (size_t i = 0; i < objects.size();i++)
    {
        for (size_t j = i + 1; j < objects.size(); j++)
        {
            if (objects[i]->GetX() == objects[j]->GetX() && objects[i]->GetY() == objects[j]->GetY())
            {
                objects[i]->OnCollisionEnter(objects[j]);
                objects[j]->OnCollisionEnter(objects[i]);
            }
        }
    }
    for (auto obj:objects)
    {
        int x =  obj->GetX();
        int y = obj->GetY();
        if (y < 0 || y >= static_cast<int>(mapData.size()) || 
            x < 0 || x >= static_cast<int>(mapData[y].size()))
        {
            continue;
        }
        if (mapData[y][x] == L'W')
        {
            obj->OnCollisionEnter(nullptr);
        }
    }
}

void World::Render(SnakeGraphics* graphics)
{
    for (int y = 0; y < (int)mapData.size(); y++)
    {
        for (int x = 0; x < (int)mapData[y].size(); x++)
        {
            wchar_t tileChar = mapData[y][x];
            if (tileChar == L'W')
            {
                graphics->PlotTile(x, y, 0,{0, 153, 0},  {0, 0, 0}, L' ');
            }
            else
            {
                graphics->PlotTile(x, y, 0,{15, 0, 15},{0, 0, 0},L' ');
            }
        }
    }
    
    for (auto obj : objects)
    {
        obj->Render(graphics);
    }

    int scoreY = graphics->GetNumRows() - 1;
    std::wstring scoreText = L"Score: " + std::to_wstring(score);
    graphics->PlotText(0, scoreY, 2, {0, 0, 0}, scoreText.c_str(), {255, 255, 255}, SnakeGraphics::Left);
}

void World::AddGameObject(GameObject* obj)
{
    objects.push_back(obj);
}

void World::RemoveGameObject(GameObject* obj)
{
    auto it = std::find(objects.begin(), objects.end(), obj);
    if (it != objects.end())
    {
        delete *it;
        objects.erase(it);
    }
}

void World::AddScore(int amountOfScore)
{
    int foundApple = 0; 
    for (auto a : objects)
    {
        AppleObject* apple = dynamic_cast<AppleObject*>(a);
        if (apple) 
        {
            foundApple++;
        }
    }
    if (foundApple == 1)
    {
        bLevelCompleted = true;
    }
    score += amountOfScore;
}
