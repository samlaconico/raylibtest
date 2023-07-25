#include "raylib.h"
#include "raymath.h"
#include "headers/state.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

State::State()
{

}

void State::update()
{
    
}

void State::draw()
{

}

void State::create(Object* o)
{
   entities.push_back(o);
}

void State::updateCamera(Camera2D* camera, Player* player)
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