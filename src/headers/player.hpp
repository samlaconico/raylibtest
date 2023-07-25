#include "object.hpp"

#pragma once

class Player : public Object
{
    public:
    Player(int x, int y);
    void update();
    void draw();
    private:   
    void input();
    void init();
    void drawDebug();
};