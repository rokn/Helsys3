#ifndef BATTLEFIELD.h
#define BATTLEFIELD.h

#include "AGE/AGE.h"

typedef struct
{
	int Width;
	int Height;
	AGE_Vector position;
} Battlefield;

void BattlefieldInit(Battlefield *, AGE_Vector, int, int);
void BattlefieldDraw(Battlefield *, int);

#endif