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

void keyboardUpdate_age();

// MOUSE INPUT

struct
{
	SDL_Point Position;
	AGE_Vector TransformedPosition;

	bool LeftIsPressed;
	bool RightIsPressed;
	bool MiddleIsPressed;
	// bool LeftJustPressed;
	// bool RightJustPressed;
	// bool MiddleJustPressed;
} AGE_Mouse;

void mouseHandleEvent_age(SDL_Event*);

#endif