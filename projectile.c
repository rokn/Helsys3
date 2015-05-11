#include "projectile.h"
#include "main.h"

const short PROJECTILES_COUNT = 1;

void set_starting_velocity(Projectile *);
void set_rotation(Projectile *);
bool check_within_boundary(Projectile *);

AGE_List *projectileSpritesList;

void LoadProjectiles()
{
	char buffer[100];
	projectileSpritesList = (AGE_List*)malloc(sizeof(AGE_List));
	AGE_ListInit(projectileSpritesList, sizeof(AGE_Sprite));
	AGE_Sprite spr;

	int i;
	
	for (i = 0; i < PROJECTILES_COUNT; ++i)
	{
		snprintf(buffer, sizeof(buffer), "Resources/Projectiles/Projectile_%d.png", i+1);

		AGE_SpriteLoad(&spr, buffer);

		AGE_ListAdd(projectileSpritesList, &spr);
	}	
}

void UnloadProjectiles()
{
	AGE_ListDestroy(projectileSpritesList);
}

void ProjectileCreate(Projectile *proj, AGE_Vector startPos, int index)
{
	proj->sprite = (AGE_Sprite*)malloc(sizeof(AGE_Sprite));
	char buffer[100];
	snprintf(buffer, sizeof(buffer), "Resources/Projectiles/Projectile_%d.png", index);
	AGE_SpriteLoad(proj->sprite, buffer);
	proj->Origin = (AGE_Vector){proj->sprite->Width/2, proj->sprite->Height/2};

	proj->index = index;
	proj->Position = startPos;
	proj->velocity = (AGE_Vector){0,0};

	switch(index)
	{
		case 1:
			proj->speed = 15;
			proj->AI = 1;
			break;
	}
}

void ProjectileSetTarget(Projectile *proj, AGE_Rect targetRect)
{
	proj->targetRect = targetRect;
	set_starting_velocity(proj);
	set_rotation(proj);
}


void ProjectileUpdate(Projectile *proj)
{
	proj->Position = AGE_VectorAdd(proj->Position, proj->velocity);

	if(!check_within_boundary(proj))
	{
		ProjectileDestroy(proj);
	}
}

void ProjectileDraw(Projectile *proj)
{
	if(proj->sprite != NULL)
	{
		AGE_SpriteRender(proj->sprite, &proj->Position, NULL, proj->rotation, NULL, SDL_FLIP_NONE, 600);
	}
}

void ProjectileDestroy(Projectile *proj)
{
	free(proj->sprite);
}


bool check_within_boundary(Projectile *proj)
{
	if(proj->Position.X + proj->sprite->Width < 0)
	{
		return false;
	}
	if(proj->Position.X > LevelWidth)
	{
		return false;
	}
	if(proj->Position.Y + proj->sprite->Height < 0)
	{
		return false;
	}
	if(proj->Position.Y > LevelHeight)
	{
		return false;
	}

	return true;
}

void set_starting_velocity(Projectile *proj)
{
	switch(proj->AI)
	{
		case 1:
			proj->velocity = AGE_Helper_FindDirection(proj->Position, AGE_Helper_RectCenter(proj->targetRect));
			proj->velocity = AGE_VectorMultiply(proj->velocity, proj->speed);
			break;
	}
}

void set_rotation(Projectile *proj)
{
	printf("%d\n",proj->rotation);
	switch(proj->AI)
	{
		case 1:
			printf("%d\n",proj->rotation);
			proj->rotation = AGE_Helper_FindRotation(proj->Position, AGE_Helper_RectCenter(proj->targetRect));
			printf("%d\n",proj->rotation);
			break;
	}
}