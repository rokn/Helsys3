#include "AGE/AGE.h"
#include "AGE/AGE_Graphics.h"
#include "AGE/AGE_Input.h"
#include "AGE/AGE_Generics.h"
#include "battlefield.h"
#include "main.h"

const int SCREEN_WIDTH = 1680;
const int SCREEN_HEIGHT = 1050;
const float CAMERA_SPEED = 600.f;

void Initialize();
void LoadContent();
void EventHandler(SDL_Event *);
void Update();
void Draw();

void CameraControl();

AGE_Sprite fpsSprite;
SDL_Color fpsTextColor;
AGE_Vector fpsTextPos;
char buffer[1024];
AGE_Sprite explosionSheet;
AGE_Animation explosionAnimation;
TTF_Font *gFont;
Battlefield *battlefield;

int main(int argc, char const *argv[])
{
	AGE_Init("AGE Test", SCREEN_WIDTH, SCREEN_HEIGHT, false);	
	Initialize();
	LoadContent();
	AGE_Run(EventHandler, Update, Draw);
	AGE_Close();
	Unload();
	return 0;
}

void Initialize()
{
	AGE_SetMaxFPS(100);
	battlefield = (Battlefield*)malloc(sizeof(Battlefield));	
	fpsTextColor = (SDL_Color){255, 0, 0, 255};
	fpsTextPos = (AGE_Vector){18.f,20.f};
	AGE_Vector v = {0,0};
	BattlefieldInit(battlefield, v, 100, 45);
}

void LoadContent()
{	
	gFont = TTF_OpenFont("Resources/Aver.ttf",16);
	AGE_SpriteLoad(&explosionSheet, "Resources/Explosion.png");	
	AGE_Animation_CreateFromSpriteSheet(&explosionAnimation, &explosionSheet, AGE_Animation_GetSpriteSheetRects(&explosionSheet, 0, 49, 100, 100), 16);
}

void Unload()
{
	BattlefieldDestroy(battlefield);
}

void EventHandler(SDL_Event *e)
{

}

void Update()
{	
	CameraControl();
	snprintf(buffer, sizeof(buffer), "FPS: %d", CURRENT_FPS);
	AGE_SpriteLoadFromText(&fpsSprite, buffer, fpsTextColor, gFont);
	AGE_Vector v = {0.f, 0.f};
	AGE_Animation_Update(&explosionAnimation, &v);
	if(AGE_KeyIsDown(SDL_SCANCODE_ESCAPE))
	{
		AGE_Exit();
	}
}

void Draw()
{
	AGE_DrawBegin();	
	AGE_SpriteRenderGUI(&fpsSprite, &fpsTextPos, NULL, 0.f, NULL, SDL_FLIP_NONE, 600);
	AGE_Animation_Draw(&explosionAnimation, 0.0f,NULL, SDL_FLIP_NONE, 16); 
	BattlefieldDraw(battlefield, 10);
	
	AGE_DrawEnd();
}

void CameraControl()
{
	bool pressed = false;
	AGE_Vector v = {0.f, 0.f};
	if(AGE_KeyIsDown(SDL_SCANCODE_LEFT))
	{
		v.X = -CAMERA_SPEED;
		pressed = true;
	}

	if(AGE_KeyIsDown(SDL_SCANCODE_RIGHT))
	{
		v.X = CAMERA_SPEED;
		pressed = true;
	}

	if(AGE_KeyIsDown(SDL_SCANCODE_UP))
	{
		v.Y = -CAMERA_SPEED;
		pressed = true;
	}

	if(AGE_KeyIsDown(SDL_SCANCODE_DOWN))
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
	AGE_GetCameraOffset().X == 5;
}