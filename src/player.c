#include "raylib.h"
#include "player.h"
#include "stdio.h"

void Init_Player(Player *player)
{
    player->anim.currentFrame = 0;
    player->anim.framesCounter = 0;
    player->anim.framesSpeed = 4;
    player->anim.frameRec = (Rectangle){0.0f, 0.0f, 32.0f, 32.0f};
    player->direction = 1.0f;
}
void player_update(Player *player)

{

    player->anim.framesCounter++;

    if (IsKeyDown(KEY_RIGHT))
    {
        player->anim.state = 1; // walk
        player->direction = 1.0f;
    }

    else
    {
        player->anim.state = 0; // idle
    }

    if (IsKeyDown(KEY_LEFT))
    {
        player->anim.state = 1;
        player->direction = -1.0f;
    }
    else
    {
        player->anim.state = 0;
    }

    if (IsKeyPressed(KEY_UP) && player->isGrounded)
    {
        player->velocity.y = -8.0f;
        player->isGrounded = false;
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        player->box.x += 5;
    }

    if (IsKeyDown(KEY_LEFT))
    {
        player->box.x -= 5;
        }

    if (player->anim.framesSpeed == 0)
        player->anim.framesSpeed = 8;

    if (player->anim.framesCounter >= (60 / player->anim.framesSpeed))
    {
        player->anim.framesCounter = 0;

        player->anim.currentFrame++;

        if (player->anim.state == 0) // idle
        {
            if (player->anim.currentFrame > 1)
                player->anim.currentFrame = 0;
            player->anim.frameRec.x = (float)player->anim.currentFrame * 32.0f;
        }
        else if (player->anim.state == 1) // walk
        {
            if (player->anim.currentFrame > 1)
                player->anim.currentFrame = 0;
            player->anim.frameRec.x = (float)(2 + player->anim.currentFrame) * 32.0f;
        }
    }
}
void player_render(Player *player, Texture2D spriteSheet)
{

    DrawTextureRec(player->spriteSheet, player->anim.frameRec, (Vector2){player->box.x, player->box.y}, WHITE);
    DrawRectangleLinesEx(player->box, 2, GREEN);
}