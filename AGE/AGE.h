#ifndef AGE_H
#define AGE_H

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#endif

#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

extern SDL_Renderer *gRenderer;
extern SDL_Window *gWindow;
extern int CURRENT_FPS;

typedef int bool;
enum { false, true };

typedef void (*EventHandle_age)(SDL_Event *event);
typedef void (*UserUpdate_age)();
typedef void (*UserDraw_age)();

typedef struct 
{
	Uint32 startTime;
	Uint32 pausedTime;

	bool IsPaused;
	bool IsStarted;

} AGE_Timer;

//Main functions

bool AGE_Init(const char* windowTitle,int screenWidth, int screenHeight, bool vSync);
void AGE_Run(EventHandle_age, UserUpdate_age, UserDraw_age);
void AGE_SetMaxFPS(int);
double AGE_DeltaSecondsGet();
Uint32 AGE_DeltaMilliSecondsGet();
void AGE_SetWindowSize(int,int);
void AGE_Close();
void AGE_Exit();

//Timer functions

void AGE_TimerInit(AGE_Timer *);
void AGE_TimerStart(AGE_Timer *);
void AGE_TimerStop(AGE_Timer *);
void AGE_TimerPause(AGE_Timer *);

Uint32 AGE_TimerGetTicks(AGE_Timer *);

//Vector

typedef struct
{
	float X;
	float Y;
}AGE_Vector;

AGE_Vector AGE_VectorAdd(AGE_Vector,AGE_Vector);
AGE_Vector AGE_VectorSubtract(AGE_Vector, AGE_Vector);
float AGE_VectorDistance(AGE_Vector, AGE_Vector);
AGE_Vector AGE_VectorMultiply(AGE_Vector, float);
AGE_Vector AGE_VectorDivide(AGE_Vector, float);
float AGE_VectorLength(AGE_Vector);
AGE_Vector AGE_VectorNormalize(AGE_Vector);

//Rectangle

typedef struct
{
	int X;
	int Y;
	int Width;
	int Height;
}AGE_Rect;

void AGE_RectSetPosition(AGE_Rect *,int,int);
bool AGE_RectIntersects(AGE_Rect, AGE_Rect);
bool AGE_RectContains(AGE_Rect, AGE_Vector);
void AGE_RectPrint(AGE_Rect);

extern AGE_Rect AGE_WindowRect;

//Helper Methods

AGE_Vector AGE_Helper_RotatedVectorMove(AGE_Vector position, float rotation, float speed);
float AGE_Helper_FindRotation(AGE_Vector, AGE_Vector, float);
AGE_Vector AGE_Helper_AngleToVector(float);

#endif