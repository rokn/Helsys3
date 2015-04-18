#include "AGE/AGE.h"
#include "AGE/AGE_Graphics.h"
#include "AGE/AGE_Input.h"
#include "AGE/AGE_Generics.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float CAMERA_SPEED = 4.f;

void LoadContent();
void EventHandler(SDL_Event *);
void Update();
void Draw();

void CameraControl();

AGE_Sprite arrow;
AGE_Sprite explosionSheet;
AGE_Animation explosionAnimation;

int main(int argc, char const *argv[])
{
	AGE_Init("AGE Test", SCREEN_WIDTH, SCREEN_HEIGHT, true);
	LoadContent();
	AGE_Run(EventHandler, Update, Draw);
	AGE_Close();	
	return 0;
}

void LoadContent()
{
	AGE_SpriteLoad(&arrow, "Arrow.png");
	AGE_SpriteLoad(&explosionSheet, "Resources/Explosion.png");	
	AGE_Animation_CreateFromSpriteSheet(&explosionAnimation, &explosionSheet, AGE_Animation_GetSpriteSheetRects(&explosionSheet, 0, 49, 200, 200), 2);
}

void EventHandler(SDL_Event *e)
{

}

void Update()
{
	CameraControl();
	AGE_Vector v = {50.f, 50.f};
	AGE_Animation_Update(&explosionAnimation, &v);
}

void Draw()
{
	AGE_DrawBegin();
	AGE_Animation_Draw(&explosionAnimation, 0.0f,NULL, SDL_FLIP_NONE, 0);
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
		AGE_DrawChangeCameraTransform(v);
	}
}
