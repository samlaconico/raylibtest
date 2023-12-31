#include "raylib.h"
#include "raymath.h"
#include "headers/player.hpp"
#include "headers/object.hpp"
#include <vector>
#include "headers/world.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 360
#define SCREEN_MULTIPLIER 3

Camera2D newCamera;
Player *playerPointer;
Player *secondPointer;

bool debug;

// NO IDEA WHY THIS DOESN'T WORK
// Player newPlayer = Player(100, 100, 1);

struct tile
{
    float x, y;
};

std::vector<tile *> tileList;

World::World()
{
    layers[0] = 0;
    layers[1] = 1;
    layers[2] = 2;
    layers[3] = 3;

    Image level = LoadImage("assets/map.png");

    Vector3 a = ColorToHSV(GetImageColor(level, 1, 2));
    std::cout << a.x << std::endl;
    std::cout << a.y << std::endl;
    std::cout << a.z << std::endl;

    for (int i = 0; i < 100; i++)
    {
        for (int g = 0; g < 100; g++)
        {
            if (std::round(ColorToHSV(GetImageColor(level, i, g)).x) == 0 && std::round(ColorToHSV(GetImageColor(level, i, g)).y * 100) == 71 && std::round(ColorToHSV(GetImageColor(level, i, g)).z * 100) == 67)
            {
                Player *o = new Player(i * 32, g * 32, 0);
                o->spriteSizeMultiplier = 1;
                playerPointer = o;
            }

            if (std::round(ColorToHSV(GetImageColor(level, i, g)).x) == 190 && std::round(ColorToHSV(GetImageColor(level, i, g)).y * 100) == 58 && std::round(ColorToHSV(GetImageColor(level, i, g)).z * 100) == 89)
            {
                tile *a = new tile;
                a->x = i * 32;
                a->y = g * 32;
                tileList.push_back(a);
            }
        }
    }

    create(playerPointer);
    playerPointer->setTag("player");
    playerPointer->world = this;

    newCamera = Camera2D();
    // newCamera.target = {(float)playerPointer->x, (float)playerPointer->y};
    newCamera.zoom = 2;
    // newCamera.offset = (Vector2){ SCREEN_WIDTH/2.0f * SCREEN_MULTIPLIER, SCREEN_HEIGHT/2.0f * SCREEN_MULTIPLIER};
    newCamera.rotation = 0.0f;

    // for (int i = 0; i < (SCREEN_WIDTH/32); i++)
    // {
    //     std::cout << i << std::endl;
    //     Player* o = new Player(i * 32, 0 , 0);
    //     o->world = this;
    //     create(o);

    // }
}

void World::create(Object *o)
{
    entityList.push_back(o);
}

void World::destroy(Object *o)
{
    for (int i = 0; i <= entityList.size(); i++)
    {
        if (entityList[i] == o)
        {
            o->unload();
            MemFree(entityList[i]);
            entityList.erase(entityList.begin() + i);
        }
    }
}

int World::getMouseX()
{
    return (((GetMouseX() - newCamera.offset.x) / newCamera.zoom) + newCamera.target.x);
}

int World::getMouseY()
{
    return (((GetMouseY() - newCamera.offset.y) / newCamera.zoom) + newCamera.target.y);
}

void World::updateCamera(Object *player, Camera2D *camera)
{
    static float minSpeed = 30;
    static float minEffectLength = 10;
    static float fractionSpeed = 3.0f;
    float deltaTime = GetFrameTime();

    camera->offset = (Vector2){SCREEN_WIDTH / 2.0f * SCREEN_MULTIPLIER, SCREEN_HEIGHT / 2.0f * SCREEN_MULTIPLIER};
    Vector2 diff = Vector2Subtract({(float)player->x + 32, (float)player->y + 32}, camera->target);
    float length = Vector2Length(diff);

    if (length > minEffectLength)
    {
        float speed = fmaxf(fractionSpeed * length, minSpeed);
        camera->target = Vector2Add(camera->target, Vector2Scale(diff, speed * deltaTime / length));
    }

    if (camera->zoom > 6.0f)
        camera->zoom = 6.0f;
    else if (camera->zoom < 0.25f)
        camera->zoom = 0.25f;

    camera->zoom += ((float)GetMouseWheelMove() * 0.05f);

    if (IsKeyPressed(KEY_R))
    {
        camera->zoom = 1.0f;
    }
}

bool World::collide(Vector2 position, Object *o)
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

bool World::collidingDirection(std::string tag, int direction, Object *o)
{
    for (int i = 0; i < entityList.size(); i++)
    {
        if (entityList[i] == o)
        {
        }
        else
        {
            if (CheckCollisionRecs(entityList[i]->hitboxRec, {o->hitboxRec.x + o->velocity.x, o->hitboxRec.y + o->velocity.y, o->hitboxRec.width, o->hitboxRec.height}) && entityList[i]->tag == tag)
            {
            }
        }
    }

    return false;
}

Object *World::collideRight(std::string tag, Object *o)
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
                if (entityList[i]->hitboxRec.x >= o->hitboxRec.x + o->hitboxRec.width - o->velocity.x)
                {
                    return entityList[i];
                }
                else
                {
                    return NULL;
                }
            }
        }
    }

    return NULL;
}

Object *World::collideUp(std::string tag, Object *o)
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
                if (entityList[i]->hitboxRec.y + entityList[i]->hitboxRec.height <= o->hitboxRec.y - o->velocity.y)
                {
                    return entityList[i];
                }
                else
                {
                    return NULL;
                }
            }
        }
    }

    return NULL;
}

Object *World::collideDown(std::string tag, Object *o)
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
                if (entityList[i]->hitboxRec.y >= o->hitboxRec.y + o->hitboxRec.height - o->velocity.y)
                {
                    return entityList[i];
                }
                else
                {
                    return NULL;
                }
            }
        }
    }

    return NULL;
}

Object *World::collideLeft(std::string tag, Object *o)
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
                if (entityList[i]->hitboxRec.x + entityList[i]->hitboxRec.width <= o->hitboxRec.x - o->velocity.x)
                {
                    return entityList[i];
                }
                else
                {
                    return NULL;
                }
            }
        }
    }

    return NULL;
}

bool World::hit(std::string tag, Object *o)
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
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Player *o = new Player(((GetMouseX() - newCamera.offset.x) / newCamera.zoom) + newCamera.target.x - 16,
                               (((GetMouseY() - newCamera.offset.y)) / newCamera.zoom) + newCamera.target.y - 16, 1);
        o->world = this;
        create(o);
    }

    if (IsKeyPressed(KEY_D))
    {
        if (debug)
            debug = false;
        else
            debug = true;
    }

    // for (int i = 0; i < entityList.size(); i++)
    // {
    //     if (collide({(float)getMouseX(), (float)getMouseY()}, entityList[i]))
    //     {
    //         entityList[i]->collide = true;
    //     }
    //     else
    //     {
    //         entityList[i]->collide = false;
    //     }
    // }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        // destroy(entityList.back());

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

    // updateCamera(playerPointer, &newCamera);

    for (auto &o : entityList)
    {
        o->update();
    }
}

void World::draw()
{
    BeginMode2D(newCamera);

    DrawText("TO BE MADE", 100, 100, 100, GRAY);
    DrawText("TO BE MADE", 100, 300, 100, GRAY);
    DrawText("TO BE MADE", 100, 500, 100, GRAY);

    for (int i = 0; i < sizeof(layers) / sizeof(int); i++)
    {
        for (int j = 0; j < entityList.size(); j++)
        {
            if (entityList[j]->layer == i)
                entityList[j]->draw();

            if (debug)
            {
                if (entityList[j]->layer == i)
                    entityList[j]->drawDebug();
            }
        }
    }

    for (auto tile : tileList)
    {
        DrawRectangle(tile->x, tile->y, 32, 32, RED);
    }

    DrawText("TO BE MADE", 100, 200, 100, GRAY);
    DrawText("TO BE MADE", 100, 400, 100, GRAY);

    EndMode2D();
}