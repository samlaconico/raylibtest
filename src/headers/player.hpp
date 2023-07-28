#include "object.hpp"

#pragma once

class Player : public Object
{
    public:
    Player(int x, int y, int layer);
    virtual void update();
    virtual void draw();
    private:   
    void input();
    void init();
    void drawDebug();
};