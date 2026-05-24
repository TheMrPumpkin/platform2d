#include <stdio.h>
#include "raylib.h"
#include "player.h"
#include "platform.h"
#include "enemy.h"
#include "map.h"
const int ScreenWidth = 800;
const int ScreenHeight = 450;

int main(void)
{
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

    enemy[0] = enemy_main(910.0f, 0.0f, 100.0f, 100.0f, 2.0f, 100.0f);
    bool is_running = true;

    Camera2D camera = {0};
    camera.target = (Vector2){player.box.x + 20.0f, player.box.y + 20.0f};
    camera.offset = (Vector2){ScreenWidth / 2.0f, ScreenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    int platform_size = sizeof(platforms) / sizeof(platforms[0]);
    int enemy_size = sizeof(enemy) / sizeof(enemy[0]);
    player.box.y = 3.0;
    player.box.x = 32.0;

    InitWindow(ScreenWidth, ScreenHeight, "GAME");
    LoadMapCSV("Tiled/world_test.csv");
    Texture2D tileset = LoadTexture("Textures/grass.png");
    Texture2D texplayer = LoadTexture("Textures/Texpumpkin.png");
    Texture2D texenemy = LoadTexture("Textures/Texapple.png");

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

        player.velocity.y += gravity;
        player.box.y += player.velocity.y;
        player.isGrounded = false;

        enemy->velocity.y += gravity;
        enemy->box.y += enemy->velocity.y;
        enemy->isGrounded = false;

        for (int i = 0; i < platform_size; i++)
        {
            if (CheckCollisionRecs(enemy->box, platforms[i].box))
            {
                if (enemy->velocity.y > 0)
                {
                    enemy->box.y = platforms[i].box.y - enemy[i].box.height; // בודק שלא נופל מהעולם
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

            if (enemy[i].HP > 0)
            {
                enemy[i].show_it = true;
                if (CheckCollisionRecs(player.box, enemy[i].box))
                {
                    enemy[i].show_it = true;
                    if ((player.box.y + player.box.height) < (enemy[i].box.y + 20))
                    {

                        enemy[i].HP -= 1;
                        player.velocity.y = -12.0f;
                        player.box.y = enemy[i].box.y - player.box.height;
                    }
                    else if (cooldownTimer <= 0.0f)
                    {
                        if (player.box.width == enemy[i].box.width)
                        {
                            cooldownTimer = cooldownDuration;
                            player.HP -= 1;
                        }
                    }
                }
            }
            else
            {
                enemy[i].show_it = false;
            }
        }

        for (int i = 0; i < enemy_size; i++)
        {
            if (player.HP <= 0)
            {
                if (IsKeyPressed(KEY_R))
                {
                    player.HP = 3;
                    enemy[i].HP = 3;
                    player.box = (Rectangle){700.0, 350.0, 100.0, 100.0};
                    enemy[i].box = (Rectangle){910.0, 0.0, 100.0, 100.0};
                };
            }
        }

        camera.target = (Vector2){player.box.x + 20, player.box.y + 20};

        BeginDrawing();
        DrawFPS(10, 10);
        ClearBackground(SKYBLUE);
        BeginMode2D(camera);
        player_render(&player, texplayer);
        DrawTileMap(tileset);
        for (int i = 0; i < enemy_size; i++)
        {
            // printf("X | %f , Y | %f\n", enemy->box.x, enemy->box.y);
            // printf("HP ENEMY %d\n", enemy->HP);
            enemy_render(&enemy[i], texenemy);
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
    CloseWindow();

    return 0;
}
