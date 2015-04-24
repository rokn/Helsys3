#include "AGE_Graphics.h"

void AGE_SpriteDestroy(AGE_Sprite *sprite)
{	
	sprite_free_age(sprite);
}

void sprite_free_age(AGE_Sprite *sprite)
{
	if( sprite->texture != NULL )
	{
		SDL_DestroyTexture( sprite->texture );
		sprite->texture = NULL;
		sprite->Width = 0;
		sprite->Height = 0;
	}
}

bool AGE_SpriteCreateBlank(AGE_Sprite *sprite, int width, int height, SDL_TextureAccess access)
{
    sprite->texture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, access, width, height);
    if( sprite->texture == NULL )
    {
        printf("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
        sprite->Width = width;
        sprite->Height = height;
    }

    return sprite->texture != NULL;
}

void AGE_SpriteSetRenderTarget(AGE_Sprite *sprite)
{
	SDL_SetRenderTarget(gRenderer, sprite->texture);
}

bool AGE_SpriteLoad(AGE_Sprite *sprite, char *path)
{
	sprite_free_age(sprite);
	
	SDL_Texture *finalTexture = NULL;
	SDL_Surface *loadedSurface = IMG_Load(path);

	if(loadedSurface == NULL)
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
	}
	else
	{

		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        finalTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );

		if( finalTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			sprite->Width = loadedSurface->w;
			sprite->Height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	sprite->texture = finalTexture;
	return finalTexture != NULL;
}

void AGE_SpriteSetColor(AGE_Sprite *sprite, Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod( sprite->texture, red, green, blue );
}

void AGE_SpriteSetBlendMode(AGE_Sprite *sprite, SDL_BlendMode blendMode)
{
	SDL_SetTextureBlendMode( sprite->texture, blendMode );
}
		
void AGE_SpriteSetAlpha(AGE_Sprite *sprite, Uint8 alpha)
{
	SDL_SetTextureAlphaMod(sprite->texture, alpha);
}
bool testIterator(void *rSprite);
void AGE_SpriteRender(AGE_Sprite *sprite, AGE_Vector *pos, AGE_Rect* clip, double rotation, AGE_Vector *origin, SDL_RendererFlip flip, short depth)
{
	SDL_Rect renderRect = {(int)pos->X, (int)pos->Y, sprite->Width, sprite->Height};

	if(clip!=NULL)
	{
		renderRect.w = clip->Width;
		renderRect.h = clip->Height;
	}

	AGE_Rect imageRect = (AGE_Rect){renderRect.x, renderRect.y, renderRect.w, renderRect.h};	

	if(!AGE_RectIntersects(imageRect, AGE_ViewRect))
	{
		return;
	}

	renderSprite_age renderSprite;
	renderSprite.sprite = sprite;
	renderSprite.pos = pos;
	renderSprite.clip = clip;
	renderSprite.renderRect = renderRect;
	renderSprite.rotation = rotation;
	renderSprite.origin = origin;
	renderSprite.flip = flip;
	renderSprite.depth = depth;

	int i;
	bool inserted = false;
	for (i = 0; i < AGE_ListGetSize(&spriteBatch_age.renderSpritesList); ++i)
	{		
		renderSprite_age rS;
		AGE_ListPeekAt(&spriteBatch_age.renderSpritesList, &rS, i);

		if(rS.depth>renderSprite.depth)
		{
			AGE_ListInsert(&spriteBatch_age.renderSpritesList, &renderSprite, i);
			inserted = true;
			break;
		}
	}
	if(!inserted)
	{
		AGE_ListAdd(&spriteBatch_age.renderSpritesList, &renderSprite);
	}
}

void AGE_SpriteRenderGUI(AGE_Sprite *sprite, AGE_Vector *pos, AGE_Rect* clip, double rotation, AGE_Vector *origin, SDL_RendererFlip flip, short depth)
{
	SDL_Rect renderRect = {(int)pos->X, (int)pos->Y, sprite->Width, sprite->Height};

	if(clip!=NULL)
	{
		renderRect.w = clip->Width;
		renderRect.h = clip->Height;
	}	

	renderSprite_age renderSprite;// = {sprite, pos, clip, rotation, origin, flip, depth};
	renderSprite.sprite = sprite;
	renderSprite.pos = pos;
	renderSprite.clip = clip;
	renderSprite.renderRect = renderRect;
	renderSprite.rotation = rotation;
	renderSprite.origin = origin;
	renderSprite.flip = flip;
	renderSprite.depth = depth;

	int i;

	for (i = 0; i < AGE_ListGetSize(&spriteBatchGui_age.renderSpritesList); ++i)
	{		
		renderSprite_age rS;
		AGE_ListPeekAt(&spriteBatchGui_age.renderSpritesList, &rS, i);

		if(rS.depth>renderSprite.depth)
		{
			AGE_ListInsert(&spriteBatchGui_age.renderSpritesList, &renderSprite, i);			
			return;
		}
	}

	AGE_ListAdd(&spriteBatchGui_age.renderSpritesList, &renderSprite);
	// SDL_RenderCopyEx(gRenderer, sprite->texture, clip, &renderRect, rotation, origin, flip);
}

bool AGE_SpriteLoadFromText(AGE_Sprite *sprite, char* text, SDL_Color textColor, TTF_Font* font)
{
	sprite_free_age(sprite);

	SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, textColor);
	
	if(textSurface == NULL)
	{
		printf("Text redner error '%s'", TTF_GetError());
	}
	else
	{		
		sprite->texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

		if(sprite->texture == NULL)
		{
			printf("Text render texture from surface error '%s'", text);
		}
		else
		{
			sprite->Width = textSurface->w;
			sprite->Height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return sprite->texture != NULL;
}

AGE_Vector AGE_GetCameraOffset()
{
	return spriteBatch_age.cameraOffset;
}