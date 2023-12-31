#pragma once

#include "raylib.h"
#include "object.hpp"
#include "player.hpp"
#include <vector>

class World
{
    public:
    World();
    virtual void update();
    virtual void draw();
    bool hit(std::string tag, Object* o);
    bool collidingDirection(std::string tag, int direction, Object* o);
    Object* collideRight(std::string tag, Object* o);
    Object* collideUp(std::string tag, Object* o);
    Object* collideLeft(std::string tag, Object* o);
    Object* collideDown(std::string tag, Object* o);
    int layers[4];
    int getMouseX();
    int getMouseY();
    bool collide(Vector2 position, Object* o);
    void create(Object* o);
    void updateCamera(Object* player, Camera2D* camera);
    void destroy(Object* o);
    bool debug;
    std::vector<Object*> entityList;
    
    private:
    //Player createdPlayer = Player(100,100,1);

    protected:
};
