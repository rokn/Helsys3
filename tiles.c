#include "tiles.h"

const int TILE_SETS_COUNT = 1;

void LoadTileSets(int tileWidth, int tileHeight)
{
	TILE_INFO.TileWidth = tileWidth;
	TILE_INFO.TileHeight = tileHeight;

	int i;
	AGE_ListInit(&TILE_INFO.tileSetsList, sizeof(AGE_Sprite));
	AGE_Sprite tileSet;
	char buffer[100];

	for (i = 0; i < TILE_SETS_COUNT; ++i)
	{
		snprintf(buffer, sizeof(buffer), "Resources/Tiles/Tiles_%d.png", i+1);
		assert(AGE_SpriteLoad(&tileSet,buffer));
		AGE_ListAdd(&TILE_INFO.tileSetsList, &tileSet);
	}

}

AGE_Rect GetSourceRect(int id, int tileSetId)
{
	AGE_Sprite tileSet;
	AGE_ListPeekAt(&TILE_INFO.tileSetsList, &tileSet, tileSetId);
	int rectsPerRow = tileSet.Width / TILE_INFO.TileWidth;
    int sourceY = id / rectsPerRow;
    int sourceX = id - sourceY * rectsPerRow;
    AGE_Rect result = {sourceX * TILE_INFO.TileWidth, sourceY * TILE_INFO.TileHeight, TILE_INFO.TileWidth, TILE_INFO.TileHeight};
    return result;
}

AGE_Sprite GetTileSet(int tileSetId)
{
	AGE_Sprite tileSet;
	AGE_ListPeekAt(&TILE_INFO.tileSetsList, &tileSet, tileSetId);
	return tileSet;
}