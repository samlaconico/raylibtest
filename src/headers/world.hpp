#pragma once

#include "raylib.h"
#include "object.hpp"
#include "player.hpp"

class World
{
    public:
    World();
    virtual void update();
    virtual void draw();
    bool hit(std::string tag, Object* o);

    private:
    void create(Object* o);
    void updateCamera(Object* player, Camera2D* camera);
    void destroy(Object* o);
    bool collide(Vector2 position, Object* o);
    std::string getLocationRelative(Vector2 position, Object*o);
    int getMouseX();
    int getMouseY();
    //Player createdPlayer = Player(100,100,1);
};
