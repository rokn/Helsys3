#include "AGE_Graphics.h"
#include "AGE_Input.h"

// bool testIterator(void *rSprite);
void renderSpriteIterator(renderSprite_age);
void renderSpriteIterator(renderSprite_age);

AGE_Rect AGE_ViewRect;

void AGE_DrawBegin()
{
	AGE_ListDestroy(&spriteBatch_age.renderSpritesList);
	AGE_ListInit(&spriteBatch_age.renderSpritesList, sizeof(renderSprite_age));

	AGE_ListDestroy(&spriteBatchGui_age.renderSpritesList);
	AGE_ListInit(&spriteBatchGui_age.renderSpritesList, sizeof(renderSprite_age));
}

void AGE_DrawEnd()
{	
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);	

	int i;
	// AGE_ListForEach(&spriteBatch_age.renderSpritesList,testIterator);
	for (i = 0; i < AGE_ListGetSize(&spriteBatch_age.renderSpritesList); ++i)
	{		
		renderSprite_age rSprite;
		AGE_ListPeekAt(&spriteBatch_age.renderSpritesList, &rSprite, i);
		renderSpriteIterator(rSprite);
	}

	for (i = 0; i < AGE_ListGetSize(&spriteBatchGui_age.renderSpritesList); ++i)
	{
		renderSprite_age rSprite;
		AGE_ListPeekAt(&spriteBatchGui_age.renderSpritesList, &rSprite, i);
		renderSpriteIteratorGUI(rSprite);
	}

	SDL_RenderPresent(gRenderer);
}

// bool testIterator(void *rSprite)
// {
// 	renderSprite_age* rS = (renderSprite_age*)rSprite;
// 	// printf("%d\n",rS->depth);
// }
void renderSpriteIterator(renderSprite_age rSprite)
{
	SDL_Point *origin;

	if(rSprite.origin==NULL)
	{
		origin = NULL;
	}
	else
	{
		origin->x = (int)rSprite.origin->X;
		origin->y = (int)rSprite.origin->Y;
	}

	rSprite.renderRect.x -= (int)camera_age.Offset.X;
	rSprite.renderRect.y -= (int)camera_age.Offset.Y;

	SDL_RenderCopyEx(gRenderer, rSprite.sprite->texture, rSprite.clip, &(rSprite.renderRect), rSprite.rotation, &origin, rSprite.flip);
	// printf("ERROR");
}

void renderSpriteIteratorGUI(renderSprite_age rSprite)
{
	SDL_Point *origin;

	if(rSprite.origin==NULL)
	{
		origin = NULL;
	}
	else
	{
		origin->x = (int)rSprite.origin->X;
		origin->y = (int)rSprite.origin->Y;
	}

	SDL_RenderCopyEx(gRenderer, rSprite.sprite->texture, rSprite.clip, &(rSprite.renderRect), rSprite.rotation, &origin, rSprite.flip);
	// printf("ERROR");
}

