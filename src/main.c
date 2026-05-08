#include <stdio.h>
#include "raylib.h"
#include "player.h"
#include "platform.h"
#include "enemy.h"

const int ScreenWidth = 800;
const int ScreenHeight = 450;

Player player = {
    .box = {
        .x = 0,
        .y = 0,
        .width = ScreenWidth / 8,
        .height = ScreenHeight / 4.5,
    },
    .isGrounded = true,
    .velocity = 0.0f,
    .HP = 10};
Enemy enemy[5];

const float gravity = 0.6f;
Platform platforms[] = {
    {.box = {.x = 400, .y = 450, .width = ScreenWidth / 1, .height = ScreenHeight / 12}},
    {.box = {.x = 400, .y = 250, .width = ScreenWidth / 8, .height = ScreenHeight / 2}}};

int main(void)
{
    enemy[0] = enemy_main(910.0f, 0.0f, 100.0f, 100.0f);

    Camera2D camera = {0};
    camera.target = (Vector2){player.box.x + 20.0f, player.box.y + 20.0f};
    camera.offset = (Vector2){ScreenWidth / 2.0f, ScreenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    int platform_size = sizeof(platforms) / sizeof(platforms[0]);
    int enemy_size = sizeof(enemy[0]) / sizeof(enemy[0]);
    player.box.x = (ScreenWidth - player.box.width) / 1;
    InitWindow(ScreenWidth, ScreenHeight, "GAME");
    Texture2D texplayer = LoadTexture("Textures/Texpumpkin.png");
    Texture2D texwall = LoadTexture("Textures/Texwall.png");
    Texture2D texenemy = LoadTexture("Textures/Texapple.png");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        for (int i = 0; i < platform_size; i++)
        {
            platform_update(&platforms[i]);
        }

        for (int i = 0; i < enemy_size; i++)
        {
            enemy_update(&enemy[i]);
        }

        player_update(&player);

        for (int i = 0; i < platform_size; i++)
        {
            if (CheckCollisionRecs(player.box, platforms[i].box))
            {
                if (IsKeyDown(KEY_RIGHT))
                    player.box.x = platforms[i].box.x - player.box.width;
                if (IsKeyDown(KEY_LEFT))
                    player.box.x = platforms[i].box.x + platforms[i].box.width;
            }
        }

        player.velocity.y += gravity;
        player.box.y += player.velocity.y;
        player.isGrounded = false;

        for (int i = 0; i < platform_size; i++)
        {
            if (CheckCollisionRecs(player.box, platforms[i].box))
            {
                if (player.velocity.y > 0)
                {
                    player.box.y = platforms[i].box.y - player.box.height;
                    player.velocity.y = 0.0f;
                    player.isGrounded = true;
                }
                else if (player.velocity.y < 0)
                {
                    player.box.y = platforms[i].box.y + platforms[i].box.height;
                    player.velocity.y = 0.0f;
                }
            }
        }

        enemy->velocity += gravity;
        enemy->box.y += enemy->velocity;
        enemy->isGrounded = false;

        for (int i = 0; i < platform_size; i++)
        {
            if (CheckCollisionRecs(enemy->box, platforms[i].box))
            {
                if (enemy->velocity > 0)
                {
                    enemy->box.y = platforms[i].box.y - enemy->box.height;
                    enemy->velocity = 0.0f;
                    enemy->isGrounded = true;
                }
                else if (player.velocity.y < 0)
                {
                    player.box.y = platforms[i].box.y + platforms[i].box.height;
                    player.velocity.y = 0.0f;
                }
            }
        }

        camera.target = (Vector2){player.box.x + 20, player.box.y + 20};

        BeginDrawing();
        DrawFPS(10, 10);
        ClearBackground(GRAY);
        BeginMode2D(camera);
        player_render(&player, texplayer);
        printf("X | %f , Y | %f\n", player.box.x, player.box.y);
        for (int i = 0; i < enemy_size; i++)
        {
            enemy_render(&enemy[i], texenemy);
        }

        for (int i = 0; i < platform_size; i++)
        {
            platform_render(&platforms[i], texwall);
        }

        EndMode2D();
        EndDrawing();
    }
    UnloadTexture(texplayer);
    UnloadTexture(texwall);
    CloseWindow();

    return 0;
}