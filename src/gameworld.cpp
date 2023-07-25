#include "raylib.h"
#include "raymath.h"
#include "headers/player.hpp"
#include "headers/object.hpp"
#include <vector>
#include <iostream>
#include "headers/gameworld.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Camera2D camera = Camera2D();
Player* playerPointer;
GameWorld::GameWorld()
{
    Player player = Player(100,100);
    playerPointer = &player;
    create(&player);

    camera.target = {(float)player.x, (float)player.y};
    camera.zoom = 1;
    camera.offset = (Vector2){ SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f};
    camera.rotation = 0.0f;
}

void GameWorld::updateCamera(Camera2D* camera, Player* player)
{
    State::updateCamera(camera, player);
}

void GameWorld::create(Object* o)
{
    State::create(o);
}

void GameWorld::update()
{
    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->update();
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        create(new Player(((GetMouseX()-camera.offset.x)/camera.zoom) + camera.target.x - 32, 
                        (((GetMouseY()-camera.offset.y))/camera.zoom) + camera.target.y - 32));
    }

    if (IsKeyPressed(KEY_D))
    {
        
    }

    updateCamera(&camera, playerPointer);

    State::update();
}


void GameWorld::draw()
{
    ClearBackground(Color{228,241,254,255});
    BeginMode2D(camera);
    DrawText("TO BE MADE", 100, 100, 100, GRAY);
    DrawText("TO BE MADE", 100, 200, 100, GRAY);
    DrawText("TO BE MADE", 100, 300, 100, GRAY);
    DrawText("TO BE MADE", 100, 400, 100, GRAY);
    DrawText("TO BE MADE", 100, 500, 100, GRAY);
    

    for (int j= 0; j < entities.size(); j++)
    {
        entities[j]->draw();
    }

    EndMode2D();

    State::draw();
}