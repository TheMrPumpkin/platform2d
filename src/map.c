#include "map.h"
#include <stdio.h>

int tileMap[MAP_H][MAP_W];

void LoadMapCSV(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("ERROR: Could not open CSV file %s\n", filename);
        return;
    }

    for (int y = 0; y < MAP_H; y++)
    {
        for (int x = 0; x < MAP_W; x++)
        {
            if (fscanf(file, "%d,", &tileMap[y][x]) != 1)
            {
                tileMap[y][x] = 0; // דיפולט לאוויר אם יש שגיאה
            }
        }
    }

    fclose(file);
    printf("SUCCESS: Map loaded from CSV!\n");
}

void DrawTileMap(Texture2D tileset)
{
    int tilesPerRow = tileset.width / 32; // בודק כמה TILDE יש
    for (int y = 0; y < MAP_H; y++)
    {
        for (int x = 0; x < MAP_W; x++)
        {
            int tile = tileMap[y][x];

            if (tile == 0)
                continue;

            tile--;

            int tileX = tile % tilesPerRow; // רוחב (tile = tileset)
            int tileY = tile / tilesPerRow; // גובה (tile = tileset)

            Rectangle sourceRec = {(float)(tileX * 32), (float)(tileY * 32), 32.0f, 32.0f};
            Rectangle destRec = {(float)(x * 32), (float)(y * 32), 32.0f, 32.0f};
            Vector2 origin = {0.0f, 0.0f};

            DrawTexturePro(tileset, sourceRec, destRec, origin, 0.0f, WHITE);
        }
    }
}