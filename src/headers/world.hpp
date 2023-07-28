#include "raylib.h"
#include "object.hpp"
#include "player.hpp"

class World
{
    public:
    World();
    virtual void update();
    virtual void draw();

    private:
    void create(Object* o);
    void updateCamera(Player* player, Camera2D* camera);
    Player createdPlayer = Player(100,100,1);
};