#include "raylib.h"
#include "raymath.h"
#include "headers/player.hpp"
#include "headers/object.hpp"
#include <vector>
#include "headers/world.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

std::vector<Object*> entityList;
Camera2D newCamera;
Player* playerPointer;

int layers[] = {0,1,2};
bool debug;

//NO IDEA WHY THIS DOESN'T WORK 
//Player newPlayer = Player(100, 100, 1);

World::World()
{
    playerPointer = new Player(100, 100, 2);
    
    create(playerPointer);
    playerPointer->setTag("player");
    playerPointer->world = this;

    newCamera = Camera2D();
    newCamera.target = {(float)playerPointer->x, (float)playerPointer->y};
    newCamera.zoom = 1;
    newCamera.offset = (Vector2){ SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f};
    newCamera.rotation = 0.0f;
}

void World::create(Object* o)
{
    entityList.push_back(o);
}

void World::destroy(Object *o)
{
    for (int i = 0; i <= entityList.size(); i++)
    {
        if (entityList[i] ==  o)
        {
            o->unload();
            free(entityList[i]);
            entityList.erase(entityList.begin() + i);
        }
    }
}

int World::getMouseX()
{
    return (((GetMouseX()-newCamera.offset.x)/newCamera.zoom) + newCamera.target.x);
}

int World::getMouseY()
{
    return (((GetMouseY()-newCamera.offset.y)/newCamera.zoom) + newCamera.target.y);
}


void World::updateCamera(Object* player, Camera2D* camera)
{
    static float minSpeed = 30;
    static float minEffectLength = 10;
    static float fractionSpeed = 3.0f;
    float deltaTime = GetFrameTime();

    camera->offset = (Vector2){ SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };
    Vector2 diff = Vector2Subtract({(float)player->x + 32, (float)player->y + 32}, camera->target);
    float length = Vector2Length(diff);

    if (length > minEffectLength)
    {
        float speed = fmaxf(fractionSpeed*length, minSpeed);
        camera->target = Vector2Add(camera->target, Vector2Scale(diff, speed*deltaTime/length));
    }

    if (camera->zoom > 3.0f) camera->zoom = 3.0f;
    else if (camera->zoom < 0.25f) camera->zoom = 0.25f;

    camera->zoom += ((float)GetMouseWheelMove()*0.05f);

    if (IsKeyPressed(KEY_R))
    {
        camera->zoom = 1.0f;
    }

}

bool World::collide(Vector2 position, Object* o)
{
    if (position.x >= (o->x + o->hitbox.offset.x) && position.x <= (o->x + o->hitbox.offset.x + o->hitbox.size.x))
    {
        if (position.y >= (o->y + o->hitbox.offset.y) && position.y <= (o->y + o->hitbox.offset.y + o->hitbox.size.y))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool World::hit(std::string tag, Object* o)
{
    for (int i = 0; i < entityList.size(); i++)
    {
        if (entityList[i] == o)
        {
            
        }
        else
        {
            if (CheckCollisionRecs(entityList[i]->hitboxRec, o->hitboxRec) && entityList[i]->tag == tag)
            {
                return true;
            }
        }
    }

    return false;
}

void World::update()
{
    updateCamera(entityList[0], &newCamera);

    for (int i = 0; i < entityList.size(); i++)
    {
        entityList[i]->update();
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        create(new Player(((GetMouseX()-newCamera.offset.x)/newCamera.zoom) + newCamera.target.x - 32, 
                        (((GetMouseY()-newCamera.offset.y))/newCamera.zoom) + newCamera.target.y - 32, 1));
    }

    if (IsKeyPressed(KEY_D))
    {
        if (debug)
            debug = false;
        else
            debug = true;
    }

    for (int i = 0; i < entityList.size(); i++)
    {
        if (collide({(float)getMouseX(), (float)getMouseY()}, entityList[i]))
        {
            entityList[i]->collide = true;
        }
        else
        {
            entityList[i]->collide = false;
        }
        
    } 

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        //destroy(entityList.back());

        if (entityList.size() > 0)
        {
            for (int i = 0; i < entityList.size(); i++)
            {
                if (collide({(float)getMouseX(), (float)getMouseY()}, entityList[i]))
                {
                    destroy(entityList[i]);
                }
                else
                {

                }
            } 
        }
    }
}

void World::draw()
{
    BeginMode2D(newCamera);

    DrawText("TO BE MADE", 100, 100, 100, GRAY);
    DrawText("TO BE MADE", 100, 300, 100, GRAY);
    DrawText("TO BE MADE", 100, 500, 100, GRAY);


    for (int i = 0; i < sizeof(layers)/sizeof(int); i++)
    {
        for (int j= 0; j < entityList.size(); j++)
        {
            if (entityList[j]->layer == i)
                entityList[j]->draw();
        }
    }

    if (debug)
    {
        for (int i = 0; i < sizeof(layers)/sizeof(int); i++)
        {
            for (int j= 0; j < entityList.size(); j++)
            {
                if (entityList[j]->layer == i)
                    entityList[j]->drawDebug();
            }
        }
    }

    DrawText("TO BE MADE", 100, 200, 100, GRAY);
    DrawText("TO BE MADE", 100, 400, 100, GRAY);

    

    EndMode2D();
}