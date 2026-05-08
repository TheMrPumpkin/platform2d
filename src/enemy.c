#include "raylib.h"
#include "stdio.h"
#include "enemy.h"

Enemy enemy_main(float x, float y, float width, float height)
{
    Enemy enemy;
    enemy.box = (Rectangle){x, y, width, height};
    enemy.velocity = 0.0f;
    enemy.isGrounded = false;
    return enemy;
}
void enemy_update(Enemy *enemy)
{
}
void enemy_render(Enemy *enemy, Texture2D texenemy)
{
    DrawTexture(texenemy, enemy->box.x, enemy->box.y, WHITE);
    DrawRectangleLinesEx(enemy->box, 2, GREEN);
}