#include "projectile.h"
#include "main.h"
#include "battle_entity.h"

const short PROJECTILES_COUNT = 1;

void set_starting_velocity(Projectile *);
void set_rotation(Projectile *);
bool check_within_boundary(Projectile *);
void init_collision_rect(Projectile *);
void update_position(Projectile*);
void update_collision_rect(Projectile *);

AGE_List *projectileSpritesList;

void ProjectileCreate(Projectile *proj, AGE_Vector startPos, int index, BattleEntity *owner)
{
	proj->IsDestroyed = false;
	proj->sprite = (AGE_Sprite*)malloc(sizeof(AGE_Sprite));
	char buffer[100];
	snprintf(buffer, sizeof(buffer), "Resources/Projectiles/Projectile_%d.png", index);
	AGE_SpriteLoad(proj->sprite, buffer);
	proj->Origin = (AGE_Vector){proj->sprite->Width/2, proj->sprite->Height/2};
	proj->destroyEvent = NULL;
	proj->owner = owner;

	proj->index = index;
	proj->Position = startPos;
	proj->Direction = (AGE_Vector){0,0};
	init_collision_rect(proj);

	switch(index)
	{
		case 1:
			proj->speed = 20;
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

void ProjectileSetDestroyEvent(Projectile *proj, DestroyEvent event)
{
	proj->destroyEvent = event;
}

void ProjectileUpdate(Projectile *proj)
{
	if(!proj->IsDestroyed)
	{
		update_position(proj);

		if(!check_within_boundary(proj))
		{
			ProjectileDestroy(proj);
		}
	}
}

void ProjectileDraw(Projectile *proj)
{
	if(!proj->IsDestroyed)
	{
		AGE_SpriteRender(proj->sprite, &proj->Position, NULL, proj->rotation, NULL, SDL_FLIP_NONE, 600);
	}
}

void ProjectileDestroy(Projectile *proj)
{
	proj->IsDestroyed = true;
	AGE_SpriteDestroy(proj->sprite);
	free(proj->sprite);

	if(proj->destroyEvent != NULL)
	{
		proj->destroyEvent(proj);
	}
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
			proj->Direction = AGE_Helper_FindDirection(proj->Position, AGE_Helper_RectCenter(proj->targetRect));			
			break;
	}
}

void set_rotation(Projectile *proj)
{	
	switch(proj->AI)
	{
		case 1:
			proj->rotation = AGE_Helper_FindRotation(proj->Position, AGE_Helper_RectCenter(proj->targetRect));
			break;
	}
}

void update_position(Projectile *proj)
{
	int i;
	
	for (i = 0; i < proj->speed; ++i)
	{
		proj->Position = AGE_VectorAdd(proj->Position, proj->Direction);
		update_collision_rect(proj);

		if(AGE_RectIntersects(proj->collisionRect,proj->targetRect))
		{
			collide_with_target(proj);
			break;
		}
	}	
}

void init_collision_rect(Projectile *proj)
{
	proj->collisionRect.X = (int)proj->Position.X - proj->sprite->Height;
	proj->collisionRect.Y = (int)proj->Position.Y - proj->sprite->Height;
	proj->collisionRect.Width = proj->sprite->Height;
	proj->collisionRect.Height = proj->sprite->Height;
}

void update_collision_rect(Projectile *proj)
{
	proj->collisionRect.X = (int)proj->Position.X - proj->sprite->Height;
	proj->collisionRect.Y = (int)proj->Position.Y - proj->sprite->Height;
}

void collide_with_target(Projectile *proj)
{
	ProjectileDestroy(proj);
}