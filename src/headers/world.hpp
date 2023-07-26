#include "raylib.h"
#include "object.hpp"
#include "player.hpp"

class World
{
    public:
    World();
    void update();
    void draw();
    

    private:
    void create(Object* o);
    void updateCamera(Player* player, Camera2D* camera);
};