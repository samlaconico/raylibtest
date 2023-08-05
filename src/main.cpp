#include "raylib.h"
#include "raymath.h"
#include "headers/player.hpp"
#include "headers/object.hpp"
#include <vector>
#include <iostream>
#include "headers/world.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 360
#define SCREEN_MULTIPLIER 3

std::vector<World*> worlds;

int main(void)
{
    
    InitWindow(SCREEN_WIDTH * SCREEN_MULTIPLIER, SCREEN_HEIGHT * SCREEN_MULTIPLIER, "TOUHOU GAME");
    SetTargetFPS(60);
    SetTraceLogLevel(0);
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
