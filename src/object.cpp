#include "headers/object.hpp"
#include "raylib.h"
#include "array"
#include <iostream>
#include <vector>
#include "raymath.h"
#include "headers/world.hpp"

Object::Object()
{
    frameCounter = 0;
    frameSpeed = 4;
    currentFrame = 0;
    frameRec = { 0.0f, 0.0f, 32, 32};
    frameAmount = 0;
}

void Object::update()
{
    animationUpdater();
}

void Object::animationUpdater()
{
    frameCounter++;

    if (frameCounter >= (60/frameSpeed))
    {
        frameCounter = 0;
        currentFrame++;
    }

    if (currentFrame >= frameAmount) 
        currentFrame = 0;

    frameRec.x = (float)((animArray[currentFrame])%(spriteTexture.width/(int)spriteSize))*spriteSize;
    frameRec.y = (float)std::floor(animArray[currentFrame]/(spriteTexture.width/spriteSize)) * spriteSize;

}

void Object::draw()
{
    DrawTexturePro(spriteTexture, frameRec, {0, 0, spriteSize * spriteSizeMultiplier, spriteSize * spriteSizeMultiplier}, {(float)-x, (float)-y}, 0.0f, WHITE);
}

void Object::addAnimation(int frames[], int speed, int frameCount, std::string name)
{
    struct animation a;

    for (int i = 0; i <= frameCount; i++)
    {
        a.frames[i] = frames[i];
    }

    a.speed = speed;
    a.frameCount = frameCount;

    animationList.push_back(a);
    animationNames.push_back(name);
}

void Object::play(std::string name)
{
    auto it = std::find(animationNames.begin(), animationNames.end(), name);
    int index;

    if (it != animationNames.end()) 
    {
        index = it - animationNames.begin();
    }
    
    playAnimation(animationList[index]);
}

void Object::playAnimation(struct animation aList)
{
    if (frameAmount != aList.frameCount)
        frameAmount = aList.frameCount;

    if (frameSpeed != aList.speed)
        frameSpeed = aList.speed;

    for (int i = 0; i <= frameAmount; i++)
    {
        if (animArray[i] != aList.frames[i])
        {
            animArray[i] = aList.frames[i];
        }
            
    }
}

void Object::setFrameSpeedMultiplier(int multiplier)
{
    frameSpeed *= multiplier;
}

void Object::drawDebug()
{
    // DrawLineEx({(float)x, (float)y}, {(float)x + objectSize, (float)y}, 3.0f, RED);
    // DrawLineEx({(float)x, (float)y}, {(float)x, (float)y + objectSize}, 3.0f, RED);
    // DrawLineEx({(float)x + objectSize, (float)y}, {(float)x + objectSize, (float)y + objectSize}, 3.0f, RED);
    // DrawLineEx({(float)x, (float)y + objectSize}, {(float)x + objectSize, (float)y + objectSize}, 3.0f, RED);

    //DrawRectangleV(Vector2Add({(float)x, (float)y}, hitbox.offset), hitbox.size, RED);

    if (collide)
    {
        DrawLineEx({(float)x + hitbox.offset.x, (float)y + hitbox.offset.y}, {(float)x + hitbox.offset.x + hitbox.size.x, (float)y + hitbox.offset.y}, 3.0f, RED);
        DrawLineEx({(float)x + hitbox.offset.x, (float)y + hitbox.offset.y}, {(float)x + hitbox.offset.x, (float)y + hitbox.offset.y + hitbox.size.y}, 3.0f, RED);
        DrawLineEx({(float)x + hitbox.offset.x + hitbox.size.x, (float)y + hitbox.offset.y}, {(float)x + hitbox.offset.x + hitbox.size.x, (float)y + hitbox.offset.y + hitbox.size.y}, 3.0f, RED);
        DrawLineEx({(float)x + hitbox.offset.x, (float)y + hitbox.offset.y + hitbox.size.y}, {(float)x + hitbox.offset.x + hitbox.size.x, (float)y + hitbox.offset.y + hitbox.size.y}, 3.0f, RED);
    }
    else
    {
        DrawLineEx({(float)x + hitbox.offset.x, (float)y + hitbox.offset.y}, {(float)x + hitbox.offset.x + hitbox.size.x, (float)y + hitbox.offset.y}, 3.0f, GREEN);
        DrawLineEx({(float)x + hitbox.offset.x, (float)y + hitbox.offset.y}, {(float)x + hitbox.offset.x, (float)y + hitbox.offset.y + hitbox.size.y}, 3.0f, GREEN);
        DrawLineEx({(float)x + hitbox.offset.x + hitbox.size.x, (float)y + hitbox.offset.y}, {(float)x + hitbox.offset.x + hitbox.size.x, (float)y + hitbox.offset.y + hitbox.size.y}, 3.0f, GREEN);
        DrawLineEx({(float)x + hitbox.offset.x, (float)y + hitbox.offset.y + hitbox.size.y}, {(float)x + hitbox.offset.x + hitbox.size.x, (float)y + hitbox.offset.y + hitbox.size.y}, 3.0f, GREEN);
    }

    std::string debugPosition = "x:" + std::to_string(x) + " " + "y:" + std::to_string(y);
    std::string debugTag = "tag: " + tag;
    
    DrawText(tag.c_str(), x, y + objectSize + 4, 12, BLUE);
    DrawText(debugPosition.c_str(), x, y - 15, 12, BLACK);
}

void Object::setTag(std::string string)
{
    tag = string;
}

void Object::unload()
{
    UnloadTexture(spritesheet);
}
