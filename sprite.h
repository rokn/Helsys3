#ifndef SPRITE_H
#define SPRITE_H

#include "magic.h"

typedef struct
{	
	SDL_Texture* texture;
	int Width;
	int Height;
} Sprite;

//void sprite_init(Sprite *);

void sprite_destroy(Sprite *);

bool sprite_load(Sprite*, char*);

bool sprite_load_from_text(Sprite* ,char*, SDL_Color);

void sprite_free(Sprite*);

void sprite_set_color(Sprite*, Uint8, Uint8, Uint8);

void sprite_set_blendMode(Sprite*, SDL_BlendMode);
		
void sprite_set_alpha(Sprite*, Uint8);

void sprite_render(Sprite*, int, int, SDL_Rect*, double, SDL_Point*, SDL_RendererFlip);

#endif