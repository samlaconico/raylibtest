#pragma once

#include "object.hpp"
#include "world.hpp"

class Player : public Object
{
    public:
    Player(int x, int y, int layer);
    void update();
    void draw();
    World* world;
    private:   
    void input();
    void init();
    void drawDebug();
    bool moving;
};