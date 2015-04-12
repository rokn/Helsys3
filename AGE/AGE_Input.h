#ifndef AGE_INPUT_H
#define AGE_INPUT_H

#include "AGE.h"

//KEYBOARD INPUT

struct
{
	const Uint8 *oldKeyboardState;
	const Uint8 *currentKeyboardState;

}AGE_Keyboard;

// bool key_is_held(KeyboardInput *, SDL_Scancode); // Not working GOTO: keyboard_input.c
// bool key_just_pressed(KeyboardInput *, SDL_Scancode); // Not working GOTO: keyboard_input.c
bool AGE_KeyIsDown(SDL_Scancode);
bool AGE_KeyIsUp(SDL_Scancode);

void AGE_KeyboardUpdate();

// MOUSE INPUT

struct
{
	int X;
	int Y;

	bool LeftIsPressed;
	bool RightIsPressed;
	bool MiddleIsPressed;
} AGE_Mouse;

void AGE_MouseHandleEvent(SDL_Event*);

#endif