#pragma once
#include "raylib.h"
#include "stdio.h"

typedef struct
{
    Rectangle frameRec;
    int currentFrame;
    int framesCounter;
    int framesSpeed;
    int state;
} AnimationData;

typedef struct
{
    Rectangle box;
    Vector2 velocity;
    AnimationData anim;
    Texture2D spriteSheet;
    bool isGrounded;
    int HP;
    float direction;

} Player;

void Init_Player(Player *player);
void player_update(Player *player);
void player_render(Player *player, Texture2D spriteSheet);