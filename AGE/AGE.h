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

extern SDL_Renderer *gRenderer;
extern SDL_Window *gWindow;

typedef int bool;
enum { false, true };

typedef struct
{
	Uint32 startTime;
	Uint32 pausedTime;

	bool IsPaused;
	bool IsStarted;

} AGE_Timer;

//Main functions

bool AGE_Init(const char* windowTitle,int screenWidth, int screenHeight, bool vSync);
void AGE_Close();

//Timer functions

void AGE_TimerInit(AGE_Timer *);
void AGE_TimerStart(AGE_Timer *);
void AGE_TimerStop(AGE_Timer *);
void AGE_TimerPause(AGE_Timer *);

Uint32 AGE_TimerGetTicks(AGE_Timer *);


#endif