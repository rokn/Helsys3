#include "AGE/AGE_Time.h"

void AGE_TimerInit(AGE_Timer *timer)
{
	timer->IsStarted = false;
	timer->IsPaused = false;
	timer->pausedTime = 0;
	timer->startTime = 0;
}

void AGE_TimerStart(AGE_Timer *timer)
{
	if(timer->IsStarted && timer->IsPaused)
	{
		timer->startTime = SDL_GetTicks() - timer->pausedTime;
		timer->IsPaused = false;
		timer->pausedTime = 0;
	}
	else
	{
		timer->IsStarted = true;
		timer->startTime = SDL_GetTicks();
		timer->IsPaused = false;
		timer->pausedTime = 0;
	}
}

void AGE_TimerStop(AGE_Timer *timer)
{
	timer->IsStarted = false;
	timer->startTime = 0;
	timer->IsPaused = 0;
	timer->pausedTime = 0;
}

void AGE_TimerPause(AGE_Timer *timer)
{
	if(timer->IsStarted && !timer->IsPaused)
	{
		timer->IsPaused = true;
		timer->pausedTime = SDL_GetTicks() - timer->startTime;
	}
}

Uint32 AGE_TimerGetTicks(AGE_Timer *timer)
{
	Uint32 timerTime = 0;

	if(timer->IsStarted)
	{
		if(timer->IsPaused)
		{
			timerTime = timer->pausedTime;
		}
		else
		{
			timerTime = SDL_GetTicks() - timer->startTime;
		}
	}

	return timerTime;
};