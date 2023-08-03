#pragma once

#include <string>
#include "raylib.h"
#include <iostream>

struct animation {
    int frames[128];
    int speed;
    int frameCount;
};

struct hitbox {
    Vector2 size;
    Vector2 offset;
};

class Object
{
    public: 
    Object();
    int x;
    int y;
    int layer;
    Texture2D spritesheet;
    Texture2D spriteTexture;
    float spriteSize;
    float spriteSizeMultiplier = 1;
    float objectSize;
    struct hitbox hitbox;
    bool collide;
    bool active;
    Rectangle hitboxRec;
    std::string direction;
    int collideDirection;
    Vector2 velocity;
    float top, bottom, left, right;

    std::string tag;
    void setTag(std::string);

    virtual void update();
    virtual void draw();
    virtual void drawDebug();
    virtual void unload();
    virtual void collision();
    void addAnimation(int frames[], int speed, int frameCount, std::string name );
    void play(std::string name);
    void setFrameSpeedMultiplier(int multiplier);
    
    private:
    std::vector<struct animation> animationList;
    std::vector<int> animationIndex;
    std::vector<std::string> animationNames;

    int frameCounter;
    int frameAmount;
    int animArray[128];
    int frameSpeed;
    int currentFrame;

    Rectangle frameRec;
    std::string playing;

    void animationUpdater();
    void playAnimation(struct animation aList);
    
};