#include "headers/player.hpp"
#include "raylib.h"
#include "raymath.h"
#include <string>

Texture2D sprites;
std::string a = "hello again";
std::string direction;
bool moving;
int sprintSpeed;
float deltaTime = GetFrameTime();
Vector2 velocity;

Player::Player(int x, int y, int layer)
{
    this->x = x;
    this->y = y;
    this->layer = layer;
    Player::init();
}

void Player::init()
{
    spritesheet = LoadTexture("assets/sprites.png");
    spriteTexture = spritesheet;
    spriteSize = 32;
    spriteSizeMultiplier = 2;
    objectSize = spriteSize * spriteSizeMultiplier;

    int walkLeft[] = {12,13,14,13};
    int walkRight[] = {24,25,26,25};
    int walkUp[] = {36,37,38,37};
    int walkDown[] = {0,1,2,1};

    int idleLeft[] = {13};
    int idleRight[] = {25};
    int idleUp[] = {37};
    int idleDown[] = {1};

    addAnimation(walkLeft, 5, 4, "walkLeft");
    addAnimation(walkRight, 5, 4, "walkRight");
    addAnimation(walkDown, 5, 4, "walkDown");
    addAnimation(walkUp, 5, 4, "walkUp");

    addAnimation(idleLeft, 0, 1, "idleLeft");
    addAnimation(idleRight, 0, 1, "idleRight");
    addAnimation(idleUp, 0, 1, "idleUp");
    addAnimation(idleDown, 0, 1, "idleDown");
    
}

void Player::update()
{
    Vector2Normalize(velocity);
    
    std::cout << direction << std::endl;

    x += velocity.x;
    y += velocity.y;

    Player::input();
    Object::update();
}

void Player::input()
{
    
    if (IsKeyDown(KEY_SPACE))
    {
        setFrameSpeedMultiplier(3);
        sprintSpeed = 3;
    }
    else
    {
        setFrameSpeedMultiplier(1);
        sprintSpeed = 1;
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        direction = "right";
        moving = true;
        velocity.x = 3 * sprintSpeed;
    } 
    else if (IsKeyDown(KEY_LEFT))
    {
        direction = "left";
        moving = true;
        velocity.x = -3 * sprintSpeed;
    }
    else
    {
        velocity.x = 0;
    }
    if (IsKeyDown(KEY_UP))
    {
        direction = "up";
        moving = true;
        velocity.y = -3 * sprintSpeed;
    } 
    else if (IsKeyDown(KEY_DOWN))
    {
        direction = "down";
        moving = true;
        velocity.y = 3 * sprintSpeed;
    }
    else
    {
        velocity.y = 0;
    }

    if (velocity.x == 0 && velocity.y == 0)
    {
        moving = false;
    }
}

void Player::draw() 
{
    if (moving == true)
    {
        if (direction == "right")
        {
            play("walkRight");
        }

        if (direction == "up")
        {
            play("walkUp");
        }

        if (direction == "down")
        {
            play("walkDown");
        }

        if (direction == "left")
        {
            play("walkLeft");
        }

    } 
    else
    {
        if (direction == "right")
        {
            play("idleRight");
        }

        if (direction == "up")
        {
            play("idleUp");
        }

        if (direction == "down")
        {
            play("idleDown");
        }

        if (direction == "left")
        {
            play("idleLeft");
        }
    }

    Object::draw();
}

void Player::drawDebug()
{   
    Object::drawDebug();
}

