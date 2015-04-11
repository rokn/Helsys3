#include "mouse_input.h"

void mouse_handle_event(SDL_Event *event)
{
	switch(event->type)
	{
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&Mouse.X, &Mouse.Y);
			break;

		case SDL_MOUSEBUTTONDOWN:
			pressButton(event);
			break;

		case SDL_MOUSEBUTTONUP:
			releaseButton(event);
			break;
	}
}

void pressButton(SDL_Event *event)
{
	switch(event->button.button)
	{
		case SDL_BUTTON_LEFT:
			Mouse.LeftIsPressed = true;
			break;
		case SDL_BUTTON_MIDDLE:
			Mouse.MiddleIsPressed = true;
			break;
		case SDL_BUTTON_RIGHT:
			Mouse.RightIsPressed = true;
			break;
	}
}

void releaseButton(SDL_Event *event)
{
	switch(event->button.button)
	{
		case SDL_BUTTON_LEFT:
			Mouse.LeftIsPressed = false;
			break;
		case SDL_BUTTON_MIDDLE:
			Mouse.MiddleIsPressed = false;
			break;
		case SDL_BUTTON_RIGHT:
			Mouse.RightIsPressed = false;
			break;
	}
}