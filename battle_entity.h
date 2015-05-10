#ifndef BATTLE_ENTITY_H
#define BATTLE_ENTITY_H

#include "main.h"
#include "battlefield.h"

typedef enum 
{
	DOWN,
	LEFT,
	RIGHT,
	UP
} Direction;

typedef struct walkSquare WalkableSquare;

struct walkSquare
{
	SDL_Point Position;
	int length;
	WalkableSquare *prev;
};

typedef struct
{
	SDL_Point Position;
	AGE_Vector FieldPosition;
	AGE_List walkingAnimations;
	Direction currentDirection;
	Battlefield* battlefield;
	AGE_Animation *currAnimation;
	bool IsMoving;
	AGE_List moveDirections;
	bool IsActive;
	int walkingDistance;
	int **fieldStatus;
	// AGE_List walkableSquares;
	WalkableSquare **walkableSquares;
	int walkableSquaresCount;
	float moveSpeed;
	int Health;
	int MaxHealth;
	int Damage;
}BattleEntity;

void BattleEntityLoad(BattleEntity*, int);
void BattleEntitySetOnField(BattleEntity*, Battlefield*, SDL_Point, Direction);
void BattleEntitySetActive(BattleEntity *);
void BattleEntityUpdate(BattleEntity*);
void BattleEntityMove(BattleEntity*, SDL_Point);
void BattleEntityDestroy(BattleEntity*);
void BattleEntityDraw(BattleEntity*);

#endif