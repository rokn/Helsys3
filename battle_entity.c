#include "battle_entity.h"
#include "tiles.h"
#include "battle.h"
#include "dictionary.h"
#include "iniparser.h"

const int BATTLE_ENTITY_DEFAULT_DEPTH = 200;

typedef struct
{
	SDL_Point Position;
	int length;
}WalkableSquare;

void mark_walkable_tiles(BattleEntity *);
void remove_walking_squares(Battlefield *);
void mark_square(BattleEntity *, int, int, int);
void find_path(BattleEntity *, SDL_Point);
void check_for_mouse_input(BattleEntity*);
bool tile_empty(Battlefield *, int, int);
void update_movement(BattleEntity*);
bool tile_obstructed(Battlefield *, int, int);
bool tile_within_battlefield(Battlefield *, int, int);
void check_for_selected_square(Battlefield *, BattleEntity*);
void entity_update_animation(BattleEntity *);
WalkableSquare find_walkable_square(BattleEntity*, SDL_Point);
void set_field_position(BattleEntity*);
void update_direction(BattleEntity *,Direction);
AGE_Vector get_true_square_coordinates(Battlefield *, SDL_Point);
void entity_change_direction(BattleEntity *);
void entity_load_stats(BattleEntity*, int);
void end_turn(BattleEntity *);

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

	for (i = 0; i < UP-DOWN+1; ++i)
	{
		int b = i*4;
		
		AGE_Animation_CreateFromSpriteSheet(&animation, spriteSheet, 
		AGE_Animation_GetSpriteSheetRects(spriteSheet, b, b+3, spriteSheet->Width / 4, spriteSheet->Height / 4), 120);
		AGE_Animation_ChangeState(&animation, false);
		AGE_ListAdd(&entity->walkingAnimations, &animation);
	}	

	entity_load_stats(entity, id);
}

void BattleEntitySetOnField(BattleEntity *entity, Battlefield * battlefield, SDL_Point position, Direction direction)
{
	entity->battlefield = battlefield;
	entity->Position = position;
	battlefield->fieldStatus[position.x][position.y] = OCCUPIED;
	entity->currentDirection = direction;
	AGE_ListPeekAt(&entity->walkingAnimations, entity->currAnimation, entity->currentDirection);
	set_field_position(entity);
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
		check_for_mouse_input(entity);

		if(entity->IsMoving)
		{
			update_movement(entity);
		}		
	}

	if(!entity->IsMoving)
	{
		set_field_position(entity);
	}

	entity_update_animation(entity);
}

void BattleEntityMove(BattleEntity *entity, SDL_Point position)
{
	entity->IsMoving = true;
	entity->battlefield->fieldStatus[entity->Position.x][entity->Position.y] = EMPTY;
	AGE_ListInit(&entity->moveDirections, sizeof(Direction));
	find_path(entity, position);
	Direction newDirection;
	if(AGE_ListGetSize(&entity->moveDirections) > 0)
	{
		AGE_ListPeekFront(&entity->moveDirections, &newDirection);
		AGE_ListRemoveFront(&entity->moveDirections);
		update_direction(entity,newDirection);
	}
	remove_walking_squares(entity->battlefield);
}

void BattleEntityDestroy(BattleEntity *entity)
{
	AGE_ListDestroy(&entity->walkingAnimations);
}

void BattleEntityDraw(BattleEntity *entity)
{	
	AGE_Animation_Draw(entity->currAnimation, 0.0f, NULL, SDL_FLIP_NONE, BATTLE_ENTITY_DEFAULT_DEPTH + entity->Position.y);
}

void update_direction(BattleEntity *entity, Direction newDirection)
{
	AGE_Animation_ChangeState(entity->currAnimation, false);
	AGE_Animation_SetIndex(entity->currAnimation, 0);
	AGE_ListReplace(&entity->walkingAnimations, entity->currAnimation, entity->currentDirection);
	entity->currentDirection = newDirection;
	AGE_ListPeekAt(&entity->walkingAnimations, entity->currAnimation, entity->currentDirection);
	AGE_Animation_ChangeState(entity->currAnimation, true);
}

void check_for_mouse_input(BattleEntity *entity)
{
	if(entity->IsActive)
	{
		if(AGE_Mouse.LeftIsPressed)
		{
			if(entity->battlefield->selectedSquare.x != -1)
			{
				if(!entity->IsMoving)
				{
					BattleEntityMove(entity, entity->battlefield->selectedSquare);
				}
			}
		}
	}
}

void update_movement(BattleEntity *entity)
{
	AGE_Vector movement = {0.f,0.f};

	switch(entity->currentDirection)
	{
		case UP:
			movement.Y -= entity->moveSpeed;

			if(entity->FieldPosition.Y+AGE_Animation_GetSize(entity->currAnimation).Height 
				<=
				 get_true_square_coordinates(entity->battlefield, entity->Position).Y)
			{
				entity_change_direction(entity);
			}
			break;
		case DOWN:
			movement.Y += entity->moveSpeed;

			if(entity->FieldPosition.Y+AGE_Animation_GetSize(entity->currAnimation).Height 
				>=
				 get_true_square_coordinates(entity->battlefield, entity->Position).Y+TILE_INFO.TileHeight * 2)
			{
				entity_change_direction(entity);
			}
			break;
		case LEFT:
			movement.X -= entity->moveSpeed;

			if(entity->FieldPosition.X+AGE_Animation_GetSize(entity->currAnimation).Width/2 
				<=
				 get_true_square_coordinates(entity->battlefield, entity->Position).X - TILE_INFO.TileWidth/2)
			{
				entity_change_direction(entity);
			}
			break;
		case RIGHT:
			movement.X += entity->moveSpeed;

			if(entity->FieldPosition.X+AGE_Animation_GetSize(entity->currAnimation).Width/2
				>=
				 get_true_square_coordinates(entity->battlefield, entity->Position).X + TILE_INFO.TileWidth * 2 - TILE_INFO.TileWidth/2)
			{
				entity_change_direction(entity);
			}
			break;
	}

	movement = AGE_VectorMultiply(movement, AGE_DeltaSecondsGet());
	entity->FieldPosition = AGE_VectorAdd(entity->FieldPosition, movement);
}

void entity_update_animation(BattleEntity *entity)
{	
	AGE_Animation_Update(entity->currAnimation, &entity->FieldPosition);
}

void entity_change_direction(BattleEntity *entity)
{	
	switch(entity->currentDirection)
	{
		case UP:
			entity->Position.y --;
			break;
		case DOWN:
			entity->Position.y ++;
			break;
		case LEFT:
			entity->Position.x --;
			break;
		case RIGHT:
			entity->Position.x ++;
			break;
	}	
	// set_field_position(entity);
	if(AGE_ListGetSize(&entity->moveDirections) > 0)
	{
		Direction newDirection;
		AGE_ListPeekFront(&entity->moveDirections, &newDirection);
		AGE_ListRemoveFront(&entity->moveDirections);
		update_direction(entity,newDirection);		
	}
	else
	{
		entity->IsMoving = false;
		entity->IsActive = false;
		AGE_Animation_ChangeState(entity->currAnimation, false);
		AGE_Animation_SetIndex(entity->currAnimation, 0);
		entity->battlefield->fieldStatus[entity->Position.x][entity->Position.y] = OCCUPIED;
		end_turn(entity);
		// BattleEntitySetActive(entity);
	}	
}

void end_turn(BattleEntity *entity)
{
	AGE_ListDestroy(&entity->moveDirections);
	AGE_ListDestroy(&entity->walkableSquares);
	BattleEndTurn();	
}

void mark_walkable_tiles(BattleEntity *entity)
{
	mark_square(entity, entity->Position.x,entity->Position.y+1, 0);
	mark_square(entity, entity->Position.x,entity->Position.y-1, 0);
	mark_square(entity, entity->Position.x+1,entity->Position.y, 0);
	mark_square(entity, entity->Position.x-1,entity->Position.y, 0);	
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

			for (i = 0; i < entity->walkableSquares.length; ++i)
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

void find_path(BattleEntity *entity, SDL_Point position)
{
	Direction direction;
	WalkableSquare square = find_walkable_square(entity, position);

	if(square.length>1)
	{
		position.x -= 1;
		WalkableSquare secondSquare = find_walkable_square(entity, position);

		if(secondSquare.length != -1 &&square.length == secondSquare.length+1)
		{
			direction = RIGHT;
			AGE_ListAddFront(&entity->moveDirections, &direction);
			find_path(entity, position);
			return;
		}

		position.x += 2;
		secondSquare = find_walkable_square(entity, position);

		if(secondSquare.length != -1 &&square.length == secondSquare.length+1)
		{
			direction = LEFT;
			AGE_ListAddFront(&entity->moveDirections, &direction);
			find_path(entity, position);
			return;
		}

		position.x -=1;
		position.y -= 1;
		secondSquare = find_walkable_square(entity, position);

		if(secondSquare.length != -1 &&square.length == secondSquare.length+1)
		{
			direction = DOWN;
			AGE_ListAddFront(&entity->moveDirections, &direction);
			find_path(entity, position);
			return;
		}

		position.y += 2;
		secondSquare = find_walkable_square(entity, position);

		if(secondSquare.length != -1 &&square.length == secondSquare.length+1)
		{
			direction = UP;
			AGE_ListAddFront(&entity->moveDirections, &direction);
			find_path(entity, position);
			return;
		}
	}
	else if(square.length == 1)
	{
		if(entity->Position.x == position.x - 1)
		{
			direction = RIGHT;
			AGE_ListAddFront(&entity->moveDirections, &direction);
			return;
		}
		if(entity->Position.x == position.x + 1)
		{
			direction = LEFT;
			AGE_ListAddFront(&entity->moveDirections, &direction);
			return;
		}
		if(entity->Position.y == position.y - 1)
		{
			direction = DOWN;
			AGE_ListAddFront(&entity->moveDirections, &direction);
			return;
		}
		if(entity->Position.y == position.y + 1)
		{
			direction = UP;
			AGE_ListAddFront(&entity->moveDirections, &direction);
			return;
		}
	}
}

WalkableSquare find_walkable_square(BattleEntity* entity, SDL_Point position)
{
	WalkableSquare square;
	int i;

	for (i = 0; i < AGE_ListGetSize(&entity->walkableSquares); ++i)
	{		
		AGE_ListPeekAt(&entity->walkableSquares, &square, i);

		if(square.Position.x == position.x && square.Position.y == position.y)
		{
			return square;
		}
	}

	square.length = -1;
	return square;
}

void set_field_position(BattleEntity *entity)
{
	entity->FieldPosition.X = entity->battlefield->Position.X + entity->Position.x * TILE_INFO.TileWidth + TILE_INFO.TileWidth/2 - AGE_Animation_GetSize(entity->currAnimation).Width/2;
	entity->FieldPosition.Y = entity->battlefield->Position.Y + entity->Position.y * TILE_INFO.TileHeight + TILE_INFO.TileHeight - AGE_Animation_GetSize(entity->currAnimation).Height;
}

AGE_Vector get_true_square_coordinates(Battlefield *battlefield, SDL_Point position)
{
	AGE_Vector v = {TILE_INFO.TileWidth * position.x + battlefield->Position.X, TILE_INFO.TileHeight * position.y + battlefield->Position.Y};
	return v;
}

void entity_load_stats(BattleEntity *entity, int id)
{
	char buffer[25];
	snprintf(buffer, sizeof(buffer), "Entities/Entity_%d.ini", id);
	dictionary * iniFile = (dictionary*)malloc(sizeof(dictionary));
	iniFile = iniparser_load(buffer);
	entity->Damage = iniparser_getint(iniFile, "Stats:Damage", 0);
	entity->Health = iniparser_getint(iniFile, "Stats:Health", 1);
	entity->MaxHealth = entity->Health;
	entity->walkingDistance = iniparser_getint(iniFile, "Stats:WalkDistance", 1);
	entity->moveSpeed = iniparser_getint(iniFile, "Stats:MoveSpeed", 100);
	iniparser_freedict(iniFile);
}