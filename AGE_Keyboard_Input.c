#include "AGE/AGE_Input.h"

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



bool AGE_KeyIsDown(SDL_Scancode scancode)
{
	return AGE_Keyboard.currentKeyboardState[scancode];
}

bool AGE_KeyIsUp(SDL_Scancode scancode)
{
	return AGE_Keyboard.currentKeyboardState[scancode];
}

void AGE_KeyboardUpdate()
{
	// input->oldKeyboardState = input->currentKeyboardState;
	AGE_Keyboard.currentKeyboardState = SDL_GetKeyboardState(NULL);
}