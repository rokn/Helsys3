#ifndef AGE_GRAPHICS_H
#define AGE_GRAPHICS_H

#include "AGE.h"

typedef struct
{	
	SDL_Texture* texture;
	int Width;
	int Height;
} AGE_Sprite;

//void sprite_init(AGE_Sprite *);

void AGE_SpriteDestroy(AGE_Sprite *);

bool AGE_SpriteLoad(AGE_Sprite*, char*);

bool AGE_SpriteLoadFromText(AGE_Sprite* ,char*, SDL_Color, TTF_Font*);

void sprite_free(AGE_Sprite*);

void AGE_SpriteSetColor(AGE_Sprite*, Uint8, Uint8, Uint8);

void AGE_SpriteSetBlendMode(AGE_Sprite*, SDL_BlendMode);
		
void AGE_SpriteSetAlpha(AGE_Sprite*, Uint8);

void AGE_SpriteRender(AGE_Sprite*, int, int, SDL_Rect*, double, SDL_Point*, SDL_RendererFlip);

#endif