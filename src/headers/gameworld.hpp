#include "raylib.h"
#include "state.hpp"

class GameWorld : State
{
    public:
    GameWorld();
    void update();
    void draw();
    void updateCamera(Camera2D* camera, Player* player);

    private:
    void create(Object* o);

};