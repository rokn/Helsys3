#include "battlefield.h"
#include "main.h"

#include "AGE/AGE.h"
#include "AGE/AGE_Graphics.h"

AGE_Sprite battlefieldSquare;
AGE_Sprite battlefieldField;
int counter;

void BattlefieldInit(Battlefield *battlefield, AGE_Vector Position, int width, int height)
{
	battlefield->Width = width;
	battlefield->Height = height;
	battlefield->position = Position;
	AGE_SpriteLoad(&battlefieldSquare, "Resources/BattlefieldSquare.png");
	AGE_SpriteCreateBlank(&battlefieldField, battlefieldSquare.Width * width, battlefieldSquare.Height * height, SDL_TEXTUREACCESS_TARGET);
	counter = 0;
}

void BattlefieldDraw(Battlefield *battlefield, int depth)
{	
	int x,y;

	AGE_Vector offset = {0.f, 0.f};
	counter ++;
	if(counter>3)
	{
		counter = 0;
		// printf("sdsds\n");
		AGE_SpriteSetRenderTarget(&battlefieldField);
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		for (x = 0; x < battlefield->Width; ++x)
		{
			for (y = 0; y < battlefield->Height; ++y)
			{			
				offset.X = x * battlefieldSquare.Width;
				offset.Y = y * battlefieldSquare.Height;
				offset = AGE_VectorAdd(battlefield->position, offset);
				AGE_Rect rect = {(int)offset.X,(int)offset.Y,battlefieldSquare.Width, battlefieldSquare.Height};
				SDL_Rect renderRect = {rect.X, rect.Y, rect.Width, rect.Height};

				if(AGE_RectIntersects(AGE_ViewRect, rect))
				{
					SDL_Rect clip = {0,0,battlefieldSquare.Width, battlefieldSquare.Height};
					SDL_RenderCopy(gRenderer, battlefieldSquare.texture, &clip, &renderRect);
				}
			}
		}

		SDL_SetRenderTarget(gRenderer, NULL);
	}

	AGE_SpriteRender(&battlefieldField, &(battlefield->position), NULL, 0.f, NULL, SDL_FLIP_NONE, depth);
}

void BattlefieldDestroy()
{
	AGE_SpriteDestroy(&battlefieldSquare);
	AGE_SpriteDestroy(&battlefieldField);
}