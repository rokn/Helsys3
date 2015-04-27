#ifndef TILES_H
#define TILES_H

#include "main.h"

extern const int TILE_SETS_COUNT;

struct
{
	AGE_List tileSetsList;
	int TileWidth;
	int TileHeight;
}TILE_INFO;

void LoadTileSets(int, int);
AGE_Rect GetSourceRect(int, int);
AGE_Sprite GetTileSet(int);

#endif