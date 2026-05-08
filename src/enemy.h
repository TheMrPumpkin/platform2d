#pragma once
#include "raylib.h"
#include "stdio.h"
typedef struct
{
    Rectangle box;
    float velocity;
    bool isGrounded;

} Enemy;
Enemy enemy_main(float x, float y, float width, float height);
void enemy_update(Enemy *enemy);
void enemy_render(Enemy *enemy, Texture2D texenemy);