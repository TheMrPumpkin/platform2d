#pragma once
#include "raylib.h"
#include "stdio.h"
typedef struct
{
    Rectangle box;
} Platform;

void platform_update(Platform *platform);
void platform_render(Platform *platform, Texture2D texwall);