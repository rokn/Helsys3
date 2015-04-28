#include "battle.h"

void BattleInitialize(AGE_List *leftTeam, AGE_List *rightTeam, int battlefieldId)
{
	CurrentBattle.leftTeamEntities = leftTeam;
	CurrentBattle.rightTeamEntities = rightTeam;
	CurrentBattle.battlefield = (Battlefield*)malloc(sizeof(Battlefield));
	BattlefieldInit(&CurrentBattle.battlefield, 1);

	int i;
	
	for (i = 0; i < AGE_ListGetSize(leftTeam); ++i)
	{
		SDL_Point entityPos = {12,2};
		BattleEntitySetOnField(&entity, battlefield, entityPos);
		BattleEntitySetActive(entity);
	}
}

void BattleUpdate()
{	
}

void BattleDraw()
{
	BattlefieldDraw(&CurrentBattle.battlefield, 10);
}

void BattleEnd()
{
	BattlefieldDestroy(&CurrentBattle.battlefield);
}