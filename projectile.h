#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "AGE/AGE.h"
#include "AGE/AGE_Graphics.h"
#include "battle_entity.h"

typedef struct projectile_t Projectile;

typedef bool (*DestroyEvent)(Projectile*);

struct projectile_t
{
	int index;
	BattleEntity *owner;
	AGE_Sprite *sprite;
	AGE_Vector Position;
	AGE_Vector Direction;
	AGE_Rect targetRect;
	float speed;
	AGE_Rect collisionRect;
	float rotation;
	int AI;
	AGE_Vector Origin;
	bool IsDestroyed;
	DestroyEvent destroyEvent;
};

void ProjectileCreate(Projectile *, AGE_Vector, int, BattleEntity*);

void ProjectileSetTarget(Projectile *, AGE_Rect);

void ProjectileSetDestroyEvent(Projectile *, DestroyEvent);

void ProjectileUpdate(Projectile *);

void ProjectileDraw(Projectile *);

void ProjectileDestroy(Projectile *);

#endif