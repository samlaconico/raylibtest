#include "headers/player.hpp"
#include "raylib.h"
#include "raymath.h"
#include <string>

int sprintSpeed;

Player::Player(int x, int y, int layer)
{
    this->x = x;
    this->y = y;
    this->layer = layer;
    active = true;
    Player::init();
}

void Player::init()
{
    spritesheet = LoadTexture("assets/sprites.png");
    
    spriteTexture = spritesheet;
    spriteSize = 32;
    spriteSizeMultiplier = 1;
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
    play("idleDown");
    
    hitbox.size = {32, 32};
    hitbox.offset = {0, 0};
    
    int rand = 2;
    switch(rand)
    {
        case 1:
        tag = "villager";
        break;

        case 2:
        tag = "monster";
        break;
        
        case 3:
        tag = "party";
        break;

        case 4:
        tag = "npc";
        break;
    }
}

void Player::update()
{
    Vector2Normalize(velocity);

    x += velocity.x;
    y += velocity.y;

    hitboxRec = {(x + hitbox.offset.x), (y + hitbox.offset.y), hitbox.size.x, hitbox.size.y};
    
    if (tag == "player")
    {
        if (world->hit("monster", this))
        {
            collide = true;
        }
        else
        {
            collide = false;
        }

        
        collision();
        input();
    }
    else
    {
        if (world->hit("player", this))
        {
            collide = true;
        }
        else
        {
            collide = false;
        }
    }

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

void Player::collision()
{
    if (world->collideRight("npc", this) != NULL)
    {
        Object* o = world->collideRight("npc", this);
        if (velocity.x > 0)
        {
            o->x = hitboxRec.x + hitboxRec.width - o->hitbox.offset.x;
        }
    }

    if (world->collideLeft("npc", this) != NULL)
    {
        Object* o = world->collideLeft("npc", this);
        if (velocity.x < 0)
        {
            o->x = hitboxRec.x - o->hitboxRec.width - o->hitbox.offset.x;
        }
    }

    if (world->collideUp("npc", this) != NULL)
    {
        Object* o = world->collideUp("npc", this);
        if (velocity.y < 0)
        {
            o->y = hitboxRec.y - o->hitboxRec.height - o->hitbox.offset.y;
        }
    }

    if (world->collideDown("npc", this) != NULL)
    {
        Object* o = world->collideDown("npc", this);
        if (velocity.y > 0)
        {
            o->y = hitboxRec.y + hitboxRec.height - o->hitbox.offset.y;
        }
    }

    if (world->collideRight("monster", this) != NULL)
    {
        Object* o = world->collideRight("monster", this);
        x = o->hitboxRec.x - hitboxRec.width - hitbox.offset.x;
        if (velocity.x > 0) velocity.x = 0;
    }

    if (world->collideLeft("monster", this) != NULL)
    {
        Object* o = world->collideLeft("monster", this);
        x = o->hitboxRec.x + o->hitboxRec.width - hitbox.offset.x;
        if (velocity.x < 0) velocity.x = 0;
    }

    if (world->collideUp("monster", this) != NULL)
    {
        Object* o = world->collideUp("monster", this);
        y = o->hitboxRec.y + o->hitboxRec.height - hitbox.offset.y;
        if (velocity.y < 0) velocity.y = 0;
    }

    if (world->collideDown("monster", this) != NULL)
    {
        Object* o = world->collideDown("monster", this);
        y = o->hitboxRec.y - hitboxRec.height - hitbox.offset.y;
        if (velocity.y > 0) velocity.y = 0;
    }
}

void Player::drawDebug()
{   
    Object::drawDebug();
}

