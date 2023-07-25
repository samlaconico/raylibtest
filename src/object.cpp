#include "headers/object.hpp"
#include "raylib.h"
#include "array"
#include <iostream>
#include <vector>

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
        //std::cout << (float)std::floor(animArray[currentFrame]/(spriteTexture.width/spriteSize)) << std::endl;
    }

    if (currentFrame >= frameAmount) currentFrame = 0;

    frameRec.x = (float)((animArray[currentFrame])%(spriteTexture.width/(int)spriteSize))*spriteSize;
    frameRec.y = (float)std::floor(animArray[currentFrame]/(spriteTexture.width/spriteSize)) * spriteSize;

    //std::cout << currentFrame << std::endl;
}

void Object::draw()
{
    DrawTexturePro(spriteTexture, frameRec, {0, 0, spriteSize * spriteSizeMultiplier, spriteSize * spriteSizeMultiplier}, {(float)-x, (float)-y}, 0.0f, WHITE);
    //DrawRectangle(x, y, 32, 32, BLUE);
}

void Object::addAnimation(int frames[], int speed, int frameCount, std::string name)
{
    struct animation a;
    for (int i = 0; i <= frameCount; i++)
    {
        a.frames[i] = frames[i];

        //std::cout << frames[i] << std::endl;;
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
      
        // calculating the index
        // of K
        index = it - animationNames.begin();
        
    }
    
    //std::cout << "playing existing anim named " << animationNames[index] << std::endl;
    playAnimation(animationList[index]);
        
    // if (std::find(animationNames.begin(), animationNames.end(), name) != animationNames.end())
    // {
    //     std::cout << "ASOIHDOIASHDOASHODHASI";
    // }
}

void Object::playAnimation(struct animation aList)
{
    //std::cout << "playing something with first frame " << aList.frames[0] << std::endl;
    if (frameAmount != aList.frameCount)
        frameAmount = aList.frameCount;

    if (frameSpeed != aList.speed)
        frameSpeed = aList.speed;

    for (int i = 0; i <= frameAmount; i++)
    {
        if (animArray[i] != aList.frames[i])
        {
            animArray[i] = aList.frames[i];
            //std::cout << animArray[i] << std::endl;
        }
            
    }

    //DrawRectangle(x, y, 32, 32, RED);
}

void Object::setFrameSpeedMultiplier(int multiplier)
{
    frameSpeed *= multiplier;
}

void Object::drawDebug()
{
    DrawLineEx({(float)x, (float)y}, {(float)x + objectSize, (float)y}, 3.0f, RED);
    DrawLineEx({(float)x, (float)y}, {(float)x, (float)y + objectSize}, 3.0f, RED);
    DrawLineEx({(float)x + objectSize, (float)y}, {(float)x + objectSize, (float)y + objectSize}, 3.0f, RED);
    DrawLineEx({(float)x, (float)y + objectSize}, {(float)x + objectSize, (float)y + objectSize}, 3.0f, RED);

    std::string debugPosition = "x:" + std::to_string(x) + " " + "y:" + std::to_string(y);

    DrawText(debugPosition.c_str(), x, y - 15, 12, BLACK);
}