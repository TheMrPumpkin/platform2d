#pragma once
#include "raylib.h"
#include "stdio.h"
typedef struct
{
    Rectangle box;
    Vector2 velocity;
    bool isGrounded;
    int HP;

} Player;

void player_update(Player *player);
void player_render(Player *player, Texture2D texplayer);