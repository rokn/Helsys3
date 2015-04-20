#ifndef AGE_GRAPHICS_H
#define AGE_GRAPHICS_H

#include "AGE.h"
#include "AGE_Generics.h"

typedef struct
{	
	SDL_Texture* texture;
	int Width;
	int Height;
} AGE_Sprite;

typedef struct{
	AGE_Sprite *sprite;
	AGE_Vector *pos;
	SDL_Rect* clip;
	SDL_Rect renderRect;
	double rotation;
	AGE_Vector* origin;
	SDL_RendererFlip flip;
	short depth;
}renderSprite_age;

struct
{
	AGE_List renderSpritesList;
	AGE_Vector cameraOffset;

} spriteBatch_age, spriteBatchGui_age;

//void sprite_init(AGE_Sprite *);

void AGE_SpriteDestroy(AGE_Sprite *);

bool AGE_SpriteLoad(AGE_Sprite*, char*);

bool AGE_SpriteLoadFromText(AGE_Sprite* ,char*, SDL_Color, TTF_Font*);

void sprite_free_age(AGE_Sprite*);

void AGE_SpriteSetColor(AGE_Sprite*, Uint8, Uint8, Uint8);

void AGE_SpriteSetBlendMode(AGE_Sprite*, SDL_BlendMode);
		
void AGE_SpriteSetAlpha(AGE_Sprite*, Uint8);

void AGE_SpriteRender(AGE_Sprite*, AGE_Vector*, AGE_Rect*, double, AGE_Vector*, SDL_RendererFlip, short);

void AGE_SpriteRenderGUI(AGE_Sprite*, AGE_Vector*, AGE_Rect*, double, AGE_Vector*, SDL_RendererFlip, short);

void AGE_DrawBegin();

void AGE_DrawSetCameraTransform(AGE_Vector);

void AGE_DrawChangeCameraTransform(AGE_Vector);

void AGE_DrawEnd();

//ANIMATION

typedef struct
{
	AGE_List clipList;
	AGE_Sprite spriteSheet;
	AGE_Vector position;
	int frameTime;
	int currFrameTime;
	int currIndex;
	SDL_Rect currentClip;
} AGE_Animation;

void AGE_Animation_CreateFromSpriteSheet(AGE_Animation *, AGE_Sprite *, AGE_List, int);

AGE_List AGE_Animation_GetSpriteSheetRects(AGE_Sprite *,int, int, int, int);

void AGE_Animation_Update(AGE_Animation*, AGE_Vector*);

void AGE_Animation_Draw(AGE_Animation*, double, AGE_Vector *, SDL_RendererFlip, short);

#endif