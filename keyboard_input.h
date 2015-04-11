#ifndef KEYBOARD_INPUT
#define KEYBOARD_INPUT

#include "magic.h"

struct
{
	const Uint8 *oldKeyboardState;
	const Uint8 *currentKeyboardState;

}Keyboard;

// bool key_is_held(KeyboardInput *, SDL_Scancode); // Not working GOTO: keyboard_input.c
// bool key_just_pressed(KeyboardInput *, SDL_Scancode); // Not working GOTO: keyboard_input.c
bool key_is_down(SDL_Scancode);
bool key_is_up(SDL_Scancode);

void keyboard_update();
#endif