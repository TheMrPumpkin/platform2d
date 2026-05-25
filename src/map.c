#include "map.h"
#include "cJSON.h"
#include <stdlib.h>

TileMap LoadMap(const char *fileName)
{
    TileMap map = {0};

    char *fileData = LoadFileText(fileName);
    cJSON *root = cJSON_Parse(fileData);

    map.width = cJSON_GetObjectItem(root, "width")->valueint;
    map.height = cJSON_GetObjectItem(root, "height")->valueint;
    map.tileWidth = 32;
    map.tileHeight = 32;

    cJSON *dataArray = cJSON_GetObjectItem(root, "layers");
    cJSON *layer = cJSON_GetArrayItem(dataArray, 0);
    cJSON *data = cJSON_GetObjectItem(layer, "data");

    int size = cJSON_GetArraySize(data);
    map.data = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        map.data[i] = cJSON_GetArrayItem(data, i)->valueint;
    }
    // READ OBJECT LAYER
    cJSON *objectLayer = cJSON_GetArrayItem(dataArray, 1);
    cJSON *objects = cJSON_GetObjectItem(objectLayer, "objects");
    int objCount = cJSON_GetArraySize(objects);
    map.collisionCount = objCount;
    for (int i = 0; i < objCount; i++)
    {
        cJSON *obj = cJSON_GetArrayItem(objects, i);
        map.collisions[i] = (Rectangle){
            cJSON_GetObjectItem(obj, "x")->valuedouble,
            cJSON_GetObjectItem(obj, "y")->valuedouble,
            cJSON_GetObjectItem(obj, "width")->valuedouble,
            cJSON_GetObjectItem(obj, "height")->valuedouble};
    }

    cJSON_Delete(root);
    UnloadFileText(fileData);
    return map;
}

void DrawMap(TileMap map, Texture2D tileset)
{
    for (int y = 0; y < map.height; y++)
    {
        for (int x = 0; x < map.width; x++)
        {

            int index = y * map.width + x;
            int tileID = map.data[index];

            if (tileID > 0)
            {

                int screenX = x * map.tileWidth;
                int screenY = y * map.tileHeight;

                int tileCol = (tileID - 1) % 5;
                int tileRow = (tileID - 1) / 5;

                Rectangle src = {tileCol * 32, tileRow * 32, 32, 32};
                Rectangle dst = {screenX, screenY, 32, 32}; // like a box
                DrawTexturePro(tileset, src, dst, (Vector2){0, 0}, 0.0f, WHITE);
                DrawRectangleLinesEx(dst, 2, GREEN);
            }
        }
    }
}