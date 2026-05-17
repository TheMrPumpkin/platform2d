#include "raylib.h"
#include "stdio.h"
#include "enemy.h"

Enemy enemy_main(float x, float y, float width, float height, float speed, float patrolRange)
{
    Enemy enemy;
    enemy.box = (Rectangle){x, y, width, height};
    enemy.velocity = (Vector2){x, y};
    enemy.isGrounded = false;
    enemy.speed = speed;
    enemy.active = true;
    enemy.pos = (Vector2){x, y};

    enemy.minX = x - patrolRange; // 810
    enemy.maxX = x + patrolRange; // 1010
    enemy.direction = 1;
    enemy.HP = 3;
    enemy.show_it = true;

    return enemy;
}
void enemy_update(Enemy *enemy)
{
    // if (!enemy->active)
    // {
    //     return;
    // }
    enemy->box.x += enemy->direction * enemy->speed;
    if (enemy->box.x >= enemy->maxX)
    {
        enemy->box.x = enemy->maxX;
        enemy->direction = -1;
    }
    if (enemy->box.x <= enemy->minX)
    {
        enemy->box.x = enemy->minX;
        enemy->direction = 1;
    }
}
void enemy_render(Enemy *enemy, Texture2D texenemy)
{
    if (enemy->show_it)
    {
        DrawTexture(texenemy, enemy->box.x, enemy->box.y, WHITE);
        DrawRectangleLinesEx(enemy->box, 2, GREEN);
    }
}