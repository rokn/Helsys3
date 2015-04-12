#ifndef TIMER_H
#define TIMER_H

#include "AGE.h"

typedef struct
{
	Uint32 startTime;
	Uint32 pausedTime;

	bool IsPaused;
	bool IsStarted;

} AGE_Timer;

void AGE_TimerInit(AGE_Timer *);
void AGE_TimerStart(AGE_Timer *);
void AGE_TimerStop(AGE_Timer *);
void AGE_TimerPause(AGE_Timer *);

Uint32 AGE_TimerGetTicks(AGE_Timer *);

#endif