#ifndef KEYBOARD_INPUT
#define KEYBOARD_INPUT

#include "magic.h"

typedef struct
{
	const Uint8 *oldKeyboardState;
	const Uint8 *currentKeyboardState;

}KeyboardInput;

bool key_is_held(KeyboardInput *, SDL_Scancode);
bool key_is_down(KeyboardInput *, SDL_Scancode);
bool key_is_up(KeyboardInput *, SDL_Scancode);
bool key_just_pressed(KeyboardInput *, SDL_Scancode);
void keyboard_update(KeyboardInput *);
#endif