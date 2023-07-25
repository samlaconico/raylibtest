#include "raylib.h"
#include "object.hpp"
#include "player.hpp"

class State
{
    public:
    State();
    virtual void update();
    virtual void draw();
    void create(Object* o);
    std::vector<Object*> entities;
    void updateCamera(Camera2D* camera, Player* player);

    
    private:
    
};
