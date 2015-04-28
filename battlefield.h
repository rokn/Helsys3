#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "main.h"

typedef struct
{
	SDL_Point position;
	AGE_Sprite sprite;
} BattlefieldObject;

typedef enum
{
	BLOCKED = -1,
	EMPTY,
	OCCUPIED,
	WALKABLE
} SquareStatus;

typedef struct
{
	int Width;
	int Height;
	AGE_Vector Position;
	BattlefieldObject *Objects;
	int ObjectsCount;
	SquareStatus **fieldStatus;
	bool IsActive;
	SDL_Point selectedSquare;
} Battlefield;

void BattlefieldInit(Battlefield *, int);
void BattlefieldDraw(Battlefield *, int);
void BattlefieldDestroy(Battlefield*);

#endif