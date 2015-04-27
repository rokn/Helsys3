#include "battle_entity.h"
#include "tiles.h"

const int BATTLE_ENTITY_DEFAULT_DEPTH = 200;

typedef struct
{
	SDL_Point Position;
	int length;
}WalkableSquare;

void mark_walkable_tiles(BattleEntity *);
void remove_walking_squares(Battlefield *);
void mark_square(BattleEntity *, int, int, int);
void find_path(BattleEntity *, SDL_Point, int);
bool tile_empty(Battlefield *, int, int);
bool tile_obstructed(Battlefield *, int, int);
bool tile_within_battlefield(Battlefield *, int, int);
void check_for_selected_square(Battlefield *, BattleEntity*);
void entity_update_animation(BattleEntity *);

void BattleEntityLoad(BattleEntity *entity, int id)
{
	AGE_ListInit(&entity->walkingAnimations, sizeof(AGE_Animation));
	AGE_ListInit(&entity->walkableSquares, sizeof(WalkableSquare));
	AGE_Sprite *spriteSheet = malloc(sizeof(AGE_Sprite));
	entity->currAnimation = malloc(sizeof(AGE_Animation));
	char buffer[100];
	int i;
	snprintf(buffer, sizeof(buffer), "Resources/Entities/Entity_%d.png", id);
	AGE_SpriteLoad(spriteSheet, buffer);
	AGE_Animation animation;
	entity->currentDirection = RIGHT;
	entity->IsMoving = false;
	entity->walkingDistance = 3;

	for (i = 0; i < UP-DOWN+1; ++i)
	{
		int b = i*4;
		
		AGE_Animation_CreateFromSpriteSheet(&animation, spriteSheet, 
		AGE_Animation_GetSpriteSheetRects(spriteSheet, b, b+3, spriteSheet->Width / 4, spriteSheet->Height / 4), 100);
		AGE_Animation_ChangeState(&animation, false);
		AGE_ListAdd(&entity->walkingAnimations, &animation);
	}

	AGE_ListPeekAt(&entity->walkingAnimations, entity->currAnimation, entity->currentDirection);
}

void BattleEntitySetOnField(BattleEntity *entity, Battlefield * battlefield, SDL_Point position)
{
	entity->battlefield = battlefield;
	entity->Position = position;
	battlefield->fieldStatus[position.x][position.y] = OCCUPIED;
	entity_update_animation(entity);
}

void BattleEntitySetActive(BattleEntity *entity)
{
	entity->IsActive = true;
	mark_walkable_tiles(entity);
}

void BattleEntityUpdate(BattleEntity *entity)
{
	if(entity->IsActive)
	{
		check_for_selected_square(entity->battlefield, entity);
		entity_update_animation(entity);
	}
}

void entity_update_animation(BattleEntity *entity)
{
	entity->FieldPosition.X = entity->battlefield->Position.X + entity->Position.x * TILE_INFO.TileWidth + TILE_INFO.TileWidth/2 - AGE_Animation_GetSize(entity->currAnimation).Width/2;
	entity->FieldPosition.Y = entity->battlefield->Position.Y + entity->Position.y * TILE_INFO.TileHeight;
	AGE_Animation_Update(entity->currAnimation, &entity->FieldPosition);
}

void mark_walkable_tiles(BattleEntity *entity)
{
	mark_square(entity, entity->Position.x+1,entity->Position.y, 0);
	mark_square(entity, entity->Position.x-1,entity->Position.y, 0);
	mark_square(entity, entity->Position.x,entity->Position.y+1, 0);
	mark_square(entity, entity->Position.x,entity->Position.y-1, 0);
}

void remove_walking_squares(Battlefield *battlefield)
{
	int x,y;

	for (x = 0; x < battlefield->Width; ++x)
	{
		for (y = 0; y < battlefield->Height; ++y)
		{
			if(battlefield->fieldStatus[x][y] == WALKABLE)
			{
				battlefield->fieldStatus[x][y] = EMPTY;
			}
		}
	}
}

void mark_square(BattleEntity *entity, int x, int y, int prevLength)
{
	if(tile_within_battlefield(entity->battlefield, x, y))
	{
		if(tile_empty(entity->battlefield, x, y))
		{
			// entity->battlefield->fieldStatus[x][y] = WALKABLE;
			SDL_Point p = {x,y};
			WalkableSquare square = {p, prevLength+1};
			AGE_ListAdd(&entity->walkableSquares, &square);
			entity->battlefield->fieldStatus[x][y] = WALKABLE;
		}
		else if(entity->battlefield->fieldStatus[x][y] == WALKABLE)
		{
			int i;

			for (i = 0; i < AGE_ListGetSize(&entity->walkableSquares); ++i)
			{
				WalkableSquare square;
				AGE_ListPeekAt(&entity->walkableSquares, &square, i);

				if(square.Position.x == x && square.Position.y == y)
				{
					if(square.length > prevLength+1)
					{
						square.length = prevLength+1;
						AGE_ListReplace(&entity->walkableSquares, &square, i);						
					}
				}
			}
		}
		else 
		{
			return;
		}
	}
	else
	{
		return;
	}
	if(prevLength+1 >= entity->walkingDistance)
	{
		return;
	}

	mark_square(entity, x+1, y, prevLength+1);
	mark_square(entity, x-1, y, prevLength+1);
	mark_square(entity, x, y+1, prevLength+1);
	mark_square(entity, x, y-1, prevLength+1);
}

bool tile_obstructed(Battlefield *battlefield, int x, int y)
{
	return battlefield->fieldStatus[x][y] == BLOCKED;
}

bool tile_empty(Battlefield *battlefield, int x, int y)
{
	return battlefield->fieldStatus[x][y] == EMPTY;
}

bool tile_within_battlefield(Battlefield *battlefield, int x, int y)
{
	return x >= 0 && x < battlefield->Width && y >= 0 && y < battlefield->Height;
}

void check_for_selected_square(Battlefield *battlefield, BattleEntity *entity)
{
	if(AGE_Mouse.TransformedPosition.X >= battlefield->Position.X && AGE_Mouse.TransformedPosition.Y >= battlefield->Position.Y)
	{		
		if(AGE_Mouse.TransformedPosition.X < battlefield->Position.X + battlefield->Width * TILE_INFO.TileWidth && 
			AGE_Mouse.TransformedPosition.Y < battlefield->Position.Y + battlefield->Height * TILE_INFO.TileHeight)
		{
			int x,y;
			x = (int)((AGE_Mouse.TransformedPosition.X - battlefield->Position.X)/TILE_INFO.TileWidth);
			y = (int)((AGE_Mouse.TransformedPosition.Y - battlefield->Position.Y)/TILE_INFO.TileHeight);

			if(battlefield->fieldStatus[x][y] == WALKABLE)
			{
				battlefield->selectedSquare.x = x;
				battlefield->selectedSquare.y = y;
			}
			else
			{
				battlefield->selectedSquare.x = -1;
				battlefield->selectedSquare.y = -1;
			}
		}
		else
		{
			battlefield->selectedSquare.x = -1;
			battlefield->selectedSquare.y = -1;
		}
	}
	else
	{
		battlefield->selectedSquare.x = -1;
		battlefield->selectedSquare.y = -1;
	}
}

void BattleEntityMove(BattleEntity *entity, SDL_Point position)
{
	
}

void BattleEntityDestroy(BattleEntity *entity)
{
	AGE_ListDestroy(&entity->walkingAnimations);
}

void BattleEntityDraw(BattleEntity *entity)
{	
	AGE_Animation_Draw(entity->currAnimation, 0.0f, NULL, SDL_FLIP_NONE, BATTLE_ENTITY_DEFAULT_DEPTH + entity->Position.y);
}