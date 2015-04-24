#include "AGE_Graphics.h"

void AGE_Animation_CreateFromSpriteSheet(AGE_Animation *animation, AGE_Sprite *spriteSheet, AGE_List clipList, int frameTime)
{
	AGE_ListInit(&(animation->clipList),sizeof(SDL_Rect));
	int i;

	for (i = 0; i < AGE_ListGetSize(&clipList); i++)
    {
    	SDL_Rect rect;
    	AGE_ListPeekAt(&clipList, &rect, i);
    	AGE_ListAdd(&(animation->clipList), &rect);
    }

    animation->frameTime = frameTime;
    animation->spriteSheet = *spriteSheet;
    animation->currFrameTime = 0;
    animation->currIndex = 0;
}

AGE_List AGE_Animation_GetSpriteSheetRects(AGE_Sprite *texture,int startingId, int endId, int frameWidth, int frameHeight)
{
    int rectsPerRow = texture->Width / frameWidth;
    AGE_List result;
    AGE_ListInit(&result ,sizeof(SDL_Rect));
    int i;

    for (i = startingId; i <= endId; i++)
    {
        int sourceY = i / rectsPerRow;
        int sourceX = i - sourceY * rectsPerRow;
        SDL_Rect rect = {sourceX * frameWidth, sourceY * frameHeight, frameWidth, frameHeight};
        AGE_ListAdd(&result, &rect);
    }

    return result;
}

void AGE_Animation_SetAlpha(AGE_Animation *animation, Uint8 alpha)
{
	AGE_SpriteSetAlpha(&(animation->spriteSheet), alpha);
}

void AGE_Animation_Update(AGE_Animation* animation, AGE_Vector *position)
{
	animation->position.X = position->X;
	animation->position.Y = position->Y;
	animation->currFrameTime += AGE_DeltaMilliSecondsGet();

	if(animation->currFrameTime>=animation->frameTime)
	{
		if(animation->currIndex < AGE_ListGetSize(&(animation->clipList)) - 1)
		{
			animation->currIndex++;			
		}
		else
		{
			animation->currIndex = 0;
		}
		
		animation->currFrameTime = 0;
	}	
}

void AGE_Animation_Draw(AGE_Animation *animation, double rotation, AGE_Vector *origin, SDL_RendererFlip flip, short depth)
{	
	
	AGE_ListPeekAt(&(animation->clipList), &(animation->currentClip), animation->currIndex);
	AGE_SpriteRender(&(animation->spriteSheet),&(animation->position), &(animation->currentClip), rotation, origin, flip, depth);
}