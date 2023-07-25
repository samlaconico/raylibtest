#include "raylib.h"
#include "raymath.h"
#include "headers/player.hpp"
#include "headers/object.hpp"
#include <vector>
#include <iostream>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

std::vector<Object*> entities;
bool debug;

void create(Object* o)
{
   entities.push_back(o);
}

void updateCamera(Camera2D* camera, Player* player)
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

int main(void)
{
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TOUHOU GAME");
    SetTargetFPS(60); 

    Player player = Player(100, 100);
    create(&player);

    Camera2D camera = Camera2D();
    camera.target = {(float)player.x, (float)player.y};
    camera.zoom = 1;
    camera.offset = (Vector2){ SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f};
    camera.rotation = 0.0f;
    
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------- -----------------------------------------

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
            if (debug)
            {
                debug = false;
            }
            else
            {
                debug = true;
            }
        }

        // Draw
        //----------------------------------------------------------------------------------
        updateCamera(&camera, &player);
        
        BeginDrawing();
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

        if (debug)
        {
            for (int k= 0; k < entities.size(); k++)
            {
                entities[k]->drawDebug();
            }
        }

        EndMode2D();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseWindow();

    return 0;
}
