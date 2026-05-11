#include "stdio.h"
#include "raylib.h"
#include "platform.h"

void platform_update(Platform *platform)
{
}
void platform_render(Platform *platform, Texture2D texwall)
{
    // platform but PRO!
    Rectangle sourceRec = {0.0f, 0.0f, (float)texwall.width, (float)texwall.height};
    Vector2 origin = {0, 0};
    Rectangle destRec = platform->box;
    DrawTexturePro(texwall, sourceRec, destRec, origin, 0.0f, WHITE);
    DrawRectangleLinesEx(platform->box, 2, GREEN);
}