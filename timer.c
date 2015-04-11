#include "timer.h"

void timer_init(Timer *timer)
{
	timer->IsStarted = false;
	timer->IsPaused = false;
	timer->pausedTime = 0;
	timer->startTime = 0;
}

void timer_start(Timer *timer)
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

void timer_stop(Timer *timer)
{
	timer->IsStarted = false;
	timer->startTime = 0;
	timer->IsPaused = 0;
	timer->pausedTime = 0;
}

void timer_pause(Timer *timer)
{
	if(timer->IsStarted && !timer->IsPaused)
	{
		timer->IsPaused = true;
		timer->pausedTime = SDL_GetTicks() - timer->startTime;
	}
}

Uint32 timer_get_time(Timer *timer)
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