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
    .HP = 3};
Enemy enemy[5];

const float gravity = 0.6f;
Platform platforms[] = {
    {.box = {.x = 400, .y = 450, .width = ScreenWidth / 1, .height = ScreenHeight / 12}},
    {.box = {.x = 400, .y = 250, .width = ScreenWidth / 8, .height = ScreenHeight / 2}}};

int main(void)
{
    enemy[0] = enemy_main(910.0f, 0.0f, 100.0f, 100.0f, 2.0f, 100.0f);
    bool is_running = true;

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

    float mid_W = ScreenWidth / 2;
    float mid_H = ScreenHeight / 2;

    float cooldownDuration = 1.2f;
    float cooldownTimer = 0.0f;
    bool isColliding = false;
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        if (cooldownTimer > 0.0f)
        {
            cooldownTimer -= GetFrameTime();
        }

        for (int i = 0; i < platform_size; i++)
        {
            platform_update(&platforms[i]);
        }

        for (int i = 0; i < enemy_size; i++)
        {
            if (player.HP > 0)
            {
                player_update(&player);
                enemy_update(&enemy[i]);
                is_running = false;
            }
        }
        if (player.HP > 0)
        {
            player_update(&player);
            is_running = false;
        }

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
        for (int i = 0; i < enemy_size; i++)
        {
            if (CheckCollisionRecs(player.box, enemy[i].box))
            {
                if (cooldownTimer <= 0.0f)
                {
                    if (player.box.width == enemy->box.width && player.box.height == enemy->box.height)
                    {
                        player.HP -= 1;
                    }
                    cooldownTimer = cooldownDuration;
                }
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

        enemy->velocity.y += gravity;
        enemy->box.y += enemy->velocity.y;
        enemy->isGrounded = false;

        for (int i = 0; i < platform_size; i++)
        {
            if (CheckCollisionRecs(enemy->box, platforms[i].box))
            {
                if (enemy->velocity.y > 0)
                {
                    enemy->box.y = platforms[i].box.y - enemy->box.height;
                    enemy->velocity.y = 0.0f;
                    enemy->isGrounded = true;
                }
                else if (player.velocity.y < 0)
                {
                    player.box.y = platforms[i].box.y + platforms[i].box.height;
                    player.velocity.y = 0.0f;
                }
            }
        }

        for (int i = 0; i < enemy_size; i++)
        {
            if (CheckCollisionRecs(player.box, enemy[i].box))
            {
                if ((player.box.y + player.box.height) < (enemy[i].box.y + 20))
                {
                    player.velocity.y = -12.0f;
                    player.box.y = enemy[i].box.y - player.box.height;
                }
            }
        }
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

        for (int i = 0; i < enemy_size; i++)
        {
            if (player.HP <= 0)
            {
                if (IsKeyPressed(KEY_R))
                {
                    player.HP = 3;
                    player.box = (Rectangle){700.0, 350.0, 100.0, 100.0};
                    enemy[i].box = (Rectangle){910.0, 0.0, 100.0, 100.0};
                };
            }
        }

        camera.target = (Vector2){player.box.x + 20, player.box.y + 20};

        BeginDrawing();
        DrawFPS(10, 10);
        ClearBackground(GRAY);
        BeginMode2D(camera);
        player_render(&player, texplayer);

        for (int i = 0; i < enemy_size; i++)
        {
            // printf("X | %f , Y | %f\n", enemy->box.x, enemy->box.y);
            enemy_render(&enemy[i], texenemy);
        }

        for (int i = 0; i < platform_size; i++)
        {
            platform_render(&platforms[i], texwall);
        }

        EndMode2D();
        if (player.HP <= 0)
        {
            player.HP = 0;
            DrawText(TextFormat("AHAHAHAHAHA!!!!", player.HP), 20, 400, 50, BLACK);
        }
        else
        {
            DrawText(TextFormat("HP %d", player.HP), 20, 400, 50, BLACK);
        }

        if (player.HP <= 0)
        {
            DrawText(TextFormat("GAME OVER!"), 250, 200, 50, RED);
            DrawText(TextFormat("PRESS R TO CONTINUE!"), 100, 250, 50, BLACK);
        }
        EndDrawing();
    }
    UnloadTexture(texplayer);
    UnloadTexture(texwall);
    CloseWindow();

    return 0;
}