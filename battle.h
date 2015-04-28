#ifndef BATTLE_H
#define BATTLE_H

#include "main.h"
#include "battlefield.h"
#include "battle_entity.h"

struct
{
	AGE_List *leftTeamEntities;
	AGE_List *rightTeamEntities;
	Battlefield *battlefield;
}CurrentBattle;

void BattleInitialize(AGE_List *leftTeam, AGE_List *rightTeam, int battlefieldId);

void BattleUpdate();

void BattleDraw();

void BattleEnd();

#endif