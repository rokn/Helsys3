#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "AGE/AGE.h"
#include "AGE/AGE_Graphics.h"

void LoadProjectiles();
void UnloadProjectiles();

typedef struct
{
	int index;
	AGE_Sprite *sprite;
	AGE_Vector Position;
	AGE_Vector velocity;
	AGE_Rect targetRect;
	float speed;
	AGE_Rect collisionRect;
	float rotation;
	int AI;
	AGE_Vector Origin;
	bool IsDestroyed;
}Projectile;

void ProjectileCreate(Projectile *, AGE_Vector, int);

void ProjectileSetTarget(Projectile *, AGE_Rect);

void ProjectileUpdate(Projectile *);

void ProjectileDraw(Projectile *);

void ProjectileDestroy(Projectile *);

#endif