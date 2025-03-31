#pragma once

class StateBase
{
public:
    virtual bool Init() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void CleanUp() = 0;
    virtual void KeyDown(int key) = 0;
};
