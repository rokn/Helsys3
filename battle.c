#include "battle.h"

void init_team(AGE_List *, int);
void update_team(AGE_List *);
void draw_team(AGE_List *);

void BattleInitialize(AGE_List *leftTeam, AGE_List *rightTeam, int battlefieldId)
{
	CurrentBattle.leftTeamEntities = leftTeam;
	CurrentBattle.rightTeamEntities = rightTeam;
	CurrentBattle.battlefield = (Battlefield*)malloc(sizeof(Battlefield));
	BattlefieldInit(CurrentBattle.battlefield, 1);
	AGE_ListInit(&CurrentBattle.entitesOrder, sizeof(EntityOrder_t));
	CurrentBattle.orderId = 0;
	init_team(leftTeam, TEAM_LEFT);
	init_team(rightTeam, TEAM_RIGHT);

	if(AGE_ListGetSize(leftTeam)>0)
	{
		BattleEntity entity;
		AGE_ListPeekAt(leftTeam, &entity, 0);
		BattleEntitySetActive(&entity);
		AGE_ListReplace(leftTeam, &entity, 0);
	}
}

void BattleUpdate()
{
	update_team(CurrentBattle.leftTeamEntities);
	update_team(CurrentBattle.rightTeamEntities);
}

void BattleDraw()
{
	draw_team(CurrentBattle.leftTeamEntities);
	draw_team(CurrentBattle.rightTeamEntities);
	BattlefieldDraw(CurrentBattle.battlefield, 10);
}

void BattleEnd()
{
	BattlefieldDestroy(CurrentBattle.battlefield);
}

void BattleEndTurn()
{
	EntityOrder_t order;
	CurrentBattle.orderId++;
	if(CurrentBattle.orderId >= AGE_ListGetSize(&CurrentBattle.entitesOrder))
	{
		CurrentBattle.orderId = 0;
	}

	AGE_ListPeekAt(&CurrentBattle.entitesOrder, &order, CurrentBattle.orderId++);

	BattleEntity entity;

	if(order.team == TEAM_LEFT)
	{
		AGE_ListPeekAt(CurrentBattle.leftTeamEntities, &entity, order.id);
		BattleEntitySetActive(&entity);
		AGE_ListReplace(CurrentBattle.leftTeamEntities, &entity, order.id);
		
	}
	else
	{
		AGE_ListPeekAt(CurrentBattle.rightTeamEntities, &entity, order.id);
		BattleEntitySetActive(&entity);
		AGE_ListReplace(CurrentBattle.rightTeamEntities, &entity, order.id);
	}
}

void init_team(AGE_List *team, int side)
{
	BattleEntity entity;
	int i;

	for (i = 0; i < AGE_ListGetSize(team); ++i)
	{
		AGE_ListPeekAt(team, &entity, i);
		SDL_Point entityPos = {0,i};
		Direction dir = RIGHT;

		if(side == 1)
		{
			entityPos.x = CurrentBattle.battlefield->Width-1;
			dir = LEFT;
		}		
		BattleEntitySetOnField(&entity, CurrentBattle.battlefield, entityPos, dir);

		AGE_ListReplace(team, &entity, i);

		EntityOrder_t order = {i, side};
		AGE_ListAdd(&CurrentBattle.entitesOrder, &order);
	}	
}

void update_team(AGE_List *team)
{
	BattleEntity entity;
	int i;	
	for (i = 0; i < AGE_ListGetSize(team); ++i)
	{
		AGE_ListPeekAt(team, &entity, i);

		BattleEntityUpdate(&entity);

		AGE_ListReplace(team, &entity, i);
	}
}

void draw_team(AGE_List *team)
{
	BattleEntity entity;
	int i;
	
	for (i = 0; i < AGE_ListGetSize(team); ++i)
	{
		AGE_ListPeekAt(team, &entity, i);

		BattleEntityDraw(&entity);

		AGE_ListReplace(team, &entity, i);
	}
}