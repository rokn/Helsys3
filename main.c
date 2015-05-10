#include "battlefield.h"
#include "main.h"
#include "tiles.h"
#include "battle_entity.h"
#include "battle.h"

const int SCREEN_WIDTH = 1680;
const int SCREEN_HEIGHT = 1050;
const float CAMERA_SPEED = 900.f;
const float MOUSE_MOVE_OFFSET = 5.f;

int LevelWidth;
int LevelHeight;

void Initialize();
void LoadContent();
void EventHandler(SDL_Event *);
void Update();
void Unload();
void Draw();

void CameraControl();
void SetCameraWithinBoundary();
void HandleMainInput();

AGE_Sprite fpsSprite;
SDL_Color fpsTextColor;
AGE_Vector fpsTextPos;
char buffer[300];
TTF_Font *gFont;
BattleEntity entity,entity2,e3;
AGE_List leftTeam,rightTeam;
int mode;

int main(int argc, char const *argv[])
{
	AGE_Init("AGE Test", SCREEN_WIDTH, SCREEN_HEIGHT, false);	
	// AGE_FullScreenBorderless();
	Initialize();
	LoadContent();
	AGE_Run(EventHandler, Update, Draw);
	Unload();
	AGE_Close();
	return 0;
}

void Initialize()
{	
	AGE_Vector v = {0,0};
	AGE_DrawSetCameraTransform(v);
	AGE_SetMaxFPS(60);
	fpsTextColor = (SDL_Color){255, 0, 0, 255};
	fpsTextPos = (AGE_Vector){18.f,20.f};

	LevelWidth = 2592;
	LevelHeight = 1728;
	AGE_ListInit(&leftTeam, sizeof(BattleEntity));
	AGE_ListInit(&rightTeam, sizeof(BattleEntity));
}

void LoadContent()
{
	gFont = TTF_OpenFont("Resources/Fonts/Aver.ttf",16);
	LoadTileSets(72, 72);

	BattleEntityLoad(&entity, 1);
	BattleEntityLoad(&entity2, 1);
	// BattleEntityLoad(&e3, 1);
	
	AGE_ListAdd(&leftTeam, &entity);
	AGE_ListAdd(&leftTeam, &entity2);

	// AGE_ListAdd(&rightTeam, &e3);
	// AGE_ListAdd(&rightTeam, &entity);
	// AGE_ListAdd(&rightTeam, &entity);

	BattleInitialize(&leftTeam, &rightTeam, 1);
}

void Unload()
{
	BattleEntityDestroy(&entity);
	BattleEntityDestroy(&entity2);
	BattleEntityDestroy(&e3);
}

void EventHandler(SDL_Event *e)
{

}

void Update()
{	
	CameraControl();//printf("%d\n",);
	snprintf(buffer, sizeof(buffer), "FPS: %d", CURRENT_FPS);
	AGE_SpriteLoadFromText(&fpsSprite, buffer, fpsTextColor, gFont);
	BattleUpdate();
	HandleMainInput();
}

void Draw()
{
	AGE_DrawBegin();	
	AGE_SpriteRenderGUI(&fpsSprite, &fpsTextPos, NULL, 0.f, NULL, SDL_FLIP_NONE, 600);	
	BattleDraw();
	AGE_DrawEnd();

}

void CameraControl()
{
	bool pressed = false;
	AGE_Vector v = {0.f, 0.f};

	if(AGE_KeyIsDown(SDL_SCANCODE_LEFT) || AGE_Mouse.Position.x <= MOUSE_MOVE_OFFSET)
	{
		v.X = -CAMERA_SPEED;
		pressed = true;
	}

	if(AGE_KeyIsDown(SDL_SCANCODE_RIGHT) || AGE_Mouse.Position.x >= AGE_WindowRect.Width - MOUSE_MOVE_OFFSET)
	{
		v.X = CAMERA_SPEED;
		pressed = true;
	}

	if(AGE_KeyIsDown(SDL_SCANCODE_UP) || AGE_Mouse.Position.y <= MOUSE_MOVE_OFFSET)
	{
		v.Y = -CAMERA_SPEED;
		pressed = true;
	}

	if(AGE_KeyIsDown(SDL_SCANCODE_DOWN) || AGE_Mouse.Position.y >= AGE_WindowRect.Height - MOUSE_MOVE_OFFSET)
	{
		v.Y = CAMERA_SPEED;
		pressed = true;
	}

	if(pressed)
	{
		AGE_DrawChangeCameraTransform(AGE_VectorMultiply(v, AGE_DeltaSecondsGet()));
	}

	SetCameraWithinBoundary();
}

void SetCameraWithinBoundary()
{
	AGE_Vector cameraOffset = AGE_GetCameraOffset();
	
	if(cameraOffset.X < 0)
	{
		cameraOffset.X = 0;
	}
	if(cameraOffset.X+AGE_ViewRect.Width > LevelWidth)
	{
		cameraOffset.X = LevelWidth - AGE_ViewRect.Width;
	}
	if(cameraOffset.Y < 0)
	{
		cameraOffset.Y = 0;
	}
	if(cameraOffset.Y+AGE_ViewRect.Height > LevelHeight)
	{
		cameraOffset.Y = LevelHeight - AGE_ViewRect.Height;
	}

	AGE_DrawSetCameraTransform(cameraOffset);
}

void HandleMainInput()
{	
	if(AGE_KeyIsDown(SDL_SCANCODE_ESCAPE))
	{		
		AGE_Exit();
	}
}