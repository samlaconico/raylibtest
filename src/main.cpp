#include "raylib.h"
#include "raymath.h"
#include "headers/player.hpp"
#include "headers/object.hpp"
#include <vector>
#include <iostream>
#include "headers/world.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

std::vector<World*> worlds;

int main(void)
{
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TOUHOU GAME");
    SetTargetFPS(60);
    World geimuWorld = World();

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------- -----------------------------------------
        geimuWorld.update();
        BeginDrawing();
        ClearBackground(Color{228,241,254,255});
        geimuWorld.draw();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseWindow();

    return 0;
}
