#ifndef	MOUSE_INPUT_H
#define MOUSE_INPUT_H

#include "magic.h"

struct
{
	int X;
	int Y;

	bool LeftIsPressed;
	bool RightIsPressed;
	bool MiddleIsPressed;
} Mouse;

void mouse_handle_event(SDL_Event*);

#endif