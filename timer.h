#ifndef TIMER_H
#define TIMER_H

#include "magic.h"

typedef struct
{
	Uint32 startTime;
	Uint32 pausedTime;

	bool IsPaused;
	bool IsStarted;

} Timer;

void timer_init(Timer *);
void timer_start(Timer *);
void timer_stop(Timer *);
void timer_pause(Timer *);

Uint32 timer_get_time(Timer *);

#endif