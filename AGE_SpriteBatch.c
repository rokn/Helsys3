#include "AGE/AGE_Graphics.h"

bool renderSpriteIterator(renderSprite_age);

void AGE_DrawBegin()
{
	AGE_ListDestroy(&spriteBatch_age.renderSpritesList);
	AGE_ListInit(&spriteBatch_age.renderSpritesList, sizeof(renderSprite_age));
}

void AGE_DrawSetCameraTransform(AGE_Vector v)
{
	spriteBatch_age.cameraOffset = v;
}

void AGE_DrawChangeCameraTransform(AGE_Vector v)
{
	spriteBatch_age.cameraOffset = AGE_VectorAdd(spriteBatch_age.cameraOffset, v);
}

void AGE_DrawEnd()
{	
	// printf("ERROr");
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);	
	// printf("ERROr");
	// AGE_ListForEach(&spriteBatch_age.renderSpritesList, renderSpriteIterator);
	int i;
	for (i = 0; i < AGE_ListGetSize(&spriteBatch_age.renderSpritesList); ++i)
	{
		renderSprite_age rSprite;
		AGE_ListPeekAt(&spriteBatch_age.renderSpritesList, &rSprite, i);
		renderSpriteIterator(rSprite);
	}
	SDL_RenderPresent(gRenderer);
}

bool renderSpriteIterator(renderSprite_age rSprite)
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

	rSprite.renderRect.x -= (int)spriteBatch_age.cameraOffset.X;
	rSprite.renderRect.y -= (int)spriteBatch_age.cameraOffset.Y;

	SDL_RenderCopyEx(gRenderer, rSprite.sprite->texture, rSprite.clip, &(rSprite.renderRect), rSprite.rotation, &origin, rSprite.flip);
	// printf("ERROR");
}