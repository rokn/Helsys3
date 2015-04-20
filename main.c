#include "AGE/AGE.h"
#include "AGE/AGE_Graphics.h"
#include "AGE/AGE_Input.h"
#include "AGE/AGE_Generics.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float CAMERA_SPEED = 350.f;

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

int main(int argc, char const *argv[])
{
	AGE_Init("AGE Test", SCREEN_WIDTH, SCREEN_HEIGHT, false);
	AGE_SetMaxFPS(1000);
	Initialize();
	LoadContent();
	AGE_Run(EventHandler, Update, Draw);
	AGE_Close();
	return 0;
}

void Initialize()
{
	fpsTextColor = (SDL_Color){0, 0, 0, 255};
	fpsTextPos = (AGE_Vector){20.f,20.f};
}

void LoadContent()
{	
	gFont = TTF_OpenFont("Resources/Aver.ttf",16);
	AGE_SpriteLoad(&explosionSheet, "Resources/Explosion.png");	
	AGE_Animation_CreateFromSpriteSheet(&explosionAnimation, &explosionSheet, AGE_Animation_GetSpriteSheetRects(&explosionSheet, 0, 49, 100, 100), 16);
}

void EventHandler(SDL_Event *e)
{

}

void Update()
{	
	CameraControl();
	snprintf(buffer, sizeof(buffer), "FPS: %lf", AGE_DeltaSecondsGet());
	AGE_SpriteLoadFromText(&fpsSprite, buffer, fpsTextColor, gFont);
	AGE_Vector v = {50.f, 50.f};
	AGE_Animation_Update(&explosionAnimation, &v);
}

void Draw()
{
	AGE_DrawBegin();	
	AGE_SpriteRenderGUI(&fpsSprite, &fpsTextPos, NULL, 0.f, NULL, SDL_FLIP_NONE, 600);
	AGE_SpriteRender(&fpsSprite, &fpsTextPos, NULL, 0.f, NULL, SDL_FLIP_NONE, 600);
	// AGE_Animation_Draw(&explosionAnimation, 0.0f,NULL, SDL_FLIP_NONE, 0);
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
		AGE_DrawChangeCameraTransform(AGE_VectorMultiply(v ,AGE_DeltaSecondsGet()));
	}
}
