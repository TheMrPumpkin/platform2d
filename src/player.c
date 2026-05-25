#include "raylib.h"
#include "player.h"
#include "stdio.h"

void player_update(Player *player)

{
    if (IsKeyPressed(KEY_UP) && player->isGrounded)
    {

        // player->box.y -= 5;
        player->velocity.y = -12.0f;
        player->isGrounded = false;
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        player->box.x += 3;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        player->box.x -= 3;
    }
}
void player_render(Player *player, Texture2D texplayer)
{

    DrawTexture(texplayer, player->box.x, player->box.y, WHITE);
    DrawRectangleLinesEx(player->box, 2, GREEN);
}