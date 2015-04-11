#include "keyboard_input.h"

bool key_is_held(KeyboardInput * input, SDL_Scancode scancode)
{
	return input->oldKeyboardState[scancode] && input->oldKeyboardState[scancode] == input->currentKeyboardState[scancode];
}

bool key_is_down(KeyboardInput *input, SDL_Scancode scancode)
{
	return input->currentKeyboardState[scancode];
}

bool key_is_up(KeyboardInput *input, SDL_Scancode scancode)
{
	return !input->currentKeyboardState[scancode];
}

bool key_just_pressed(KeyboardInput *input, SDL_Scancode scancode)
{
	if(input->currentKeyboardState[SDL_SCANCODE_0])
	{
		printf("%d",input->oldKeyboardState[scancode]);
	}
	
	return input->currentKeyboardState[scancode] && input->oldKeyboardState[scancode] != input->currentKeyboardState[scancode];
}

void keyboard_update(KeyboardInput *input)
{
	printf("%d\n",input->oldKeyboardState[SDL_SCANCODE_LEFT]);
	input->oldKeyboardState = input->currentKeyboardState;
	input->currentKeyboardState = SDL_GetKeyboardState(NULL);
}