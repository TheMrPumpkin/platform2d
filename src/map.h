#ifndef MAP_H
#define MAP_H

#include "raylib.h"

#define MAP_W 32
#define MAP_H 32

extern int tileMap[MAP_H][MAP_W];

void LoadMapCSV(const char *filename);
void DrawTileMap(Texture2D tileset);

#endif