#ifndef BATTLEFIELD.h
#define BATTLEFIELD.h

#include "main.h"

typedef struct
{
	SDL_Point position;
	AGE_Sprite sprite;
}BattlefieldObject;

typedef struct
{
	int Width;
	int Height;
	AGE_Vector Position;
	BattlefieldObject *Objects;
	int ObjectsCount;
	short **fieldStatus;
} Battlefield;

void BattlefieldInit(Battlefield *, AGE_Vector, int);
void BattlefieldDraw(Battlefield *, int);

#endif