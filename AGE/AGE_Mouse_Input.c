#include "AGE_Input.h"
#include "AGE_Graphics.h"

void mouseHandleEvent_age(SDL_Event *event)
{
	switch(event->type)
	{
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&AGE_Mouse.Position.x, &AGE_Mouse.Position.y);
			AGE_Mouse.TransformedPosition.X = AGE_Mouse.Position.x + camera_age.Offset.X;
			AGE_Mouse.TransformedPosition.Y = AGE_Mouse.Position.y + camera_age.Offset.Y;
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
			AGE_Mouse.LeftIsPressed = true;
			break;
		case SDL_BUTTON_MIDDLE:
			AGE_Mouse.MiddleIsPressed = true;
			break;
		case SDL_BUTTON_RIGHT:
			AGE_Mouse.RightIsPressed = true;
			break;
	}
}

void releaseButton(SDL_Event *event)
{
	switch(event->button.button)
	{
		case SDL_BUTTON_LEFT:
			AGE_Mouse.LeftIsPressed = false;
			break;
		case SDL_BUTTON_MIDDLE:
			AGE_Mouse.MiddleIsPressed = false;
			break;
		case SDL_BUTTON_RIGHT:
			AGE_Mouse.RightIsPressed = false;
			break;
	}
}