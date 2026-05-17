#pragma once
#include "raylib.h"
#include "stdio.h"
typedef struct
{
    Rectangle box;
    Vector2 velocity;
    bool isGrounded;
    float speed;
    bool active;
    Vector2 pos;
    float minX;
    float maxX;
    float direction;
    int HP;
    bool show_it;

} Enemy;
Enemy enemy_main(float x, float y, float width, float height, float speed, float patrolRange);
void enemy_update(Enemy *enemy);
void enemy_render(Enemy *enemy, Texture2D texenemy);