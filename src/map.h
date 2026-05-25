#ifndef MAP_H
#define MAP_H

#include "raylib.h"

typedef struct
{
    int width;
    int height;
    int tileWidth;  // 32
    int tileHeight; // 32
    int *data;      // ALL THE DATA
    Rectangle collisions[100];
    int collisionCount;
} TileMap;

TileMap LoadMap(const char *fileName);
void DrawMap(TileMap map, Texture2D tileset);
void UnloadMap(TileMap map);

#endif