#ifndef BATTLE_H
#define BATTLE_H

#include "main.h"
#include "battlefield.h"
#include "battle_entity.h"

enum{TEAM_LEFT,TEAM_RIGHT};

typedef struct
{
	int id;
	int team;
}EntityOrder_t;

struct
{
	AGE_List *leftTeamEntities;
	AGE_List *rightTeamEntities;
	AGE_List entitesOrder;
	Battlefield *battlefield;
	int orderId;
}CurrentBattle;

void BattleInitialize(AGE_List *leftTeam, AGE_List *rightTeam, int battlefieldId);

void BattleUpdate();

void BattleDraw();

void BattleEndTurn();

void BattleEnd();

#endif