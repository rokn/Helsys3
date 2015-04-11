#include "keyboard_input.h"

//TODO: Think of a way to implement | reminder: problem is pointers of oldState


// bool key_is_held(KeyboardInput * input, SDL_Scancode scancode)
// {
// 	return input->oldKeyboardState[scancode] && input->oldKeyboardState[scancode] == input->currentKeyboardState[scancode];
// }


// bool key_just_pressed(KeyboardInput *input, SDL_Scancode scancode)
// {
// 	if(input->currentKeyboardState[SDL_SCANCODE_0])
// 	{
// 		printf("%d",input->oldKeyboardState[scancode]);
// 	}

// 	return input->currentKeyboardState[scancode] && input->oldKeyboardState[scancode] != input->currentKeyboardState[scancode];
// }



bool key_is_down(SDL_Scancode scancode)
{
	return Keyboard.currentKeyboardState[scancode];
}

bool key_is_up(SDL_Scancode scancode)
{
	return Keyboard.currentKeyboardState[scancode];
}

void keyboard_update()
{
	// input->oldKeyboardState = input->currentKeyboardState;
	Keyboard.currentKeyboardState = SDL_GetKeyboardState(NULL);
}