#include "battlefield.h"
#include "tiles.h"

const int BATTLEFIELD_OBJECTS_COUNT = 1;

AGE_Sprite battlefieldSquare;
AGE_Sprite battlefieldField;
int counter;
AGE_List objectsList;
AGE_Sprite surroundings;

void read_battlefield_file(Battlefield *battlefield, int battlefieldId)
{
	int i, x;
	FILE *file;
	char *mode = "r";
	char buffer[100];
	snprintf(buffer, sizeof(buffer), "Levels/Level_%d.txt", battlefieldId);

	file = fopen(buffer, mode);

	if (file == NULL) {
	  fprintf(stderr, "Can't open input file %s!\n", buffer);
	  exit(1);
	}

	fscanf(file, "%d %d", &battlefield->Width, &battlefield->Height);

	battlefield->fieldStatus = malloc(sizeof(short*) * battlefield->Width);

	for (i = 0; i < battlefield->Width; ++i)
	{
		battlefield->fieldStatus[i] = malloc(sizeof(*battlefield->fieldStatus[i]) * battlefield->Height);
		for (x = 0; x < battlefield->Height; ++x)
		{
			battlefield->fieldStatus[i][x] = 0;
		}
	}

	fscanf(file, "%d", &battlefield->ObjectsCount);
	battlefield->Objects = (BattlefieldObject*)malloc(sizeof(BattlefieldObject) * battlefield->ObjectsCount);
	int id;
	SDL_Point position;
	BattlefieldObject object;

	for (i = 0; i < battlefield->ObjectsCount; ++i)
	{
		fscanf(file, "%d %d %d", &id, &position.x, &position.y);
		assert(id>=1 && id <= BATTLEFIELD_OBJECTS_COUNT);
		object.position = position;
		AGE_ListPeekAt(&objectsList, &object.sprite, id-1);
		battlefield->Objects[i] = object;
		int w,h,y;
		w = object.sprite.Width / battlefieldSquare.Width;
		h = object.sprite.Height / battlefieldSquare.Height;

		for (x = position.x; x < w + position.x; ++x)
		{
			for (y = position.y; y < h + position.y; ++y)
			{
				battlefield->fieldStatus[x][y] = -1;
			}
		}
	}

	snprintf(buffer, sizeof(buffer), "Resources/Battlefield/Surroundings_%d.png", battlefieldId);

	AGE_SpriteLoad(&surroundings, buffer);

	fclose(file);
}

void BattlefieldLoad()
{
	assert(AGE_SpriteLoad(&battlefieldSquare, "Resources/Battlefield/BattlefieldSquare.png"));
	assert(AGE_SpriteCreateBlank(&battlefieldField, LevelWidth, LevelHeight, SDL_TEXTUREACCESS_TARGET));
	AGE_ListInit(&objectsList, sizeof(AGE_Sprite));
	AGE_Sprite objectSprite;
	int i;
	char buffer[100];

	for (i = 0; i < BATTLEFIELD_OBJECTS_COUNT; ++i)
	{
		snprintf(buffer, sizeof(buffer), "Resources/Battlefield/Object_%d.png", i+1);
		AGE_SpriteLoad(&objectSprite, buffer);
		AGE_ListAdd(&objectsList, &objectSprite);
	}
}

void BattlefieldInit(Battlefield *battlefield, int battlefieldId)
{
	BattlefieldLoad();
	battlefield->Position = (AGE_Vector){216,288};;
	AGE_SpriteSetBlendMode(&battlefieldField,SDL_BLENDMODE_BLEND);
	read_battlefield_file(battlefield, battlefieldId);
	counter = 0;
}

void BattlefieldDraw(Battlefield *battlefield, int depth)
{	
	int x,y;

	AGE_Vector offset = {0.f, 0.f};
	counter ++;
	AGE_Sprite tileSet;
	SDL_Rect renderRect;
	SDL_Rect clip;
	AGE_Rect rect;
	if(counter>0)
	{
		counter = 0;
		AGE_SpriteSetRenderTarget(&battlefieldField);
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		
		for (x = 0; x < LevelWidth/TILE_INFO.TileWidth; ++x)
		{
			for (y = 0; y < LevelHeight/TILE_INFO.TileHeight; ++y)
			{				
				offset.X = x * TILE_INFO.TileWidth;
				offset.Y = y * TILE_INFO.TileHeight;
				renderRect = (SDL_Rect){(int)offset.X, (int)offset.Y, battlefieldSquare.Width, battlefieldSquare.Height};
				rect = (AGE_Rect){renderRect.x, renderRect.y , renderRect.w, renderRect.h};

				if(AGE_RectIntersects(AGE_ViewRect, rect))
				{					
					tileSet = GetTileSet(0);
					AGE_Rect ageClip;
					ageClip = GetSourceRect(1,0);
					clip = (SDL_Rect){ageClip.X, ageClip.Y, ageClip.Width, ageClip.Height};
					if(AGE_KeyIsDown(SDL_SCANCODE_D))
					{
						AGE_SpriteRender(&tileSet, &offset, &rect, 0.0f, NULL, SDL_FLIP_NONE, 80);
					}
					SDL_RenderCopy(gRenderer, tileSet.texture, &clip, &renderRect);
				}
			}
		}

		BattlefieldObject object;
		for (x = 0; x < battlefield->ObjectsCount; ++x)
		{
			object = battlefield->Objects[x];
			offset.X = object.position.x * battlefieldSquare.Width;
			offset.Y = object.position.y * battlefieldSquare.Height;
			offset = AGE_VectorAdd(battlefield->Position, offset);
			renderRect = (SDL_Rect){(int)offset.X, (int)offset.Y, object.sprite.Width, object.sprite.Height};
			rect = (AGE_Rect){renderRect.x, renderRect.y , renderRect.w, renderRect.h};

			if(AGE_RectIntersects(AGE_ViewRect, rect))
			{					
				clip = (SDL_Rect){0,0,object.sprite.Width, object.sprite.Height};				
				SDL_RenderCopy(gRenderer, object.sprite.texture, &clip, &renderRect);
			}
		}
		for (x = 0; x < battlefield->Width; ++x)
		{
			for (y = 0; y < battlefield->Height; ++y)
			{
				if(battlefield->fieldStatus[x][y] != -1)
				{	
					offset.X = x * battlefieldSquare.Width;
					offset.Y = y * battlefieldSquare.Height;
					offset = AGE_VectorAdd(battlefield->Position, offset);
					renderRect = (SDL_Rect){(int)offset.X, (int)offset.Y, battlefieldSquare.Width, battlefieldSquare.Height};
					rect = (AGE_Rect){renderRect.x, renderRect.y , renderRect.w, renderRect.h};

					if(AGE_RectIntersects(AGE_ViewRect, rect))
					{					
						clip = (SDL_Rect){0,0,battlefieldSquare.Width, battlefieldSquare.Height};				
						SDL_RenderCopy(gRenderer, battlefieldSquare.texture, &clip, &renderRect);
					}
				}
			}
		}

		for (x = 0; x < LevelWidth/surroundings.Width+1; ++x)
		{
			offset.X = x * surroundings.Width;
			offset.Y = 0;
			renderRect = (SDL_Rect){(int)offset.X, (int)offset.Y, surroundings.Width, surroundings.Height};
			rect = (AGE_Rect){renderRect.x, renderRect.y , renderRect.w, renderRect.h};

			if(AGE_RectIntersects(AGE_ViewRect, rect))
			{					
				clip = (SDL_Rect){0,0, surroundings.Width, surroundings.Height};				
				SDL_RenderCopy(gRenderer, surroundings.texture, &clip, &renderRect);
			}

			offset.Y = battlefield->Height * battlefieldSquare.Height + battlefield->Position.Y;
			renderRect = (SDL_Rect){(int)offset.X, (int)offset.Y, surroundings.Width, surroundings.Height};
			rect = (AGE_Rect){renderRect.x, renderRect.y , renderRect.w, renderRect.h};

			if(AGE_RectIntersects(AGE_ViewRect, rect))
			{					
				clip = (SDL_Rect){0,0, surroundings.Width, surroundings.Height};				
				SDL_RenderCopy(gRenderer, surroundings.texture, &clip, &renderRect);
			}
		}

		SDL_SetRenderTarget(gRenderer, NULL);
	}

	AGE_Vector v = {0,0};
	AGE_SpriteRender(&battlefieldField, &v, NULL, 0.f, NULL, SDL_FLIP_NONE, depth);
}

void BattlefieldDestroy()
{	
	AGE_SpriteDestroy(&battlefieldSquare);
	AGE_SpriteDestroy(&battlefieldField);
	AGE_ListDestroy(&objectsList);
}