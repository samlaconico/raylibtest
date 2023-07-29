#pragma once

#include "object.hpp"

class Player : public Object
{
    public:
    Player(int x, int y, int layer);
    void update();
    void draw();
    private:   
    void input();
    void init();
    void drawDebug();
    Vector2 velocity;
    bool moving;
};