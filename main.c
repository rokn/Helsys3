#include "AGE/AGE.h"
#include "AGE/AGE_Graphics.h"
#include "AGE/AGE_Input.h"
#include "AGE/AGE_Generics.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / 60;

bool LoadContent();
bool intlistForeach(void*);

bool LoadContent()
{
	//Loading success flag
	// bool success = true;

	// gFont = TTF_OpenFont("Resources/Aver.ttf", 16);
	// if(gFont == NULL)
	// {
	// 	printf("Font load error 'Aver' Error: %s\n", TTF_GetError());
	// 	success = false;
	// }
	// else
	// {
	// 	SDL_Color textColor = {0,0,0};
	// 	sprite_init(&leftButtonText);

		// if(!sprite_load_from_text(&leftButtonText, "The quick brown fox jumps over the lazy dog", textColor))
		// if(!sprite_load(&leftButtonText, "leftButtonText.png"))
		// {
			// success = false;
		// }
	// }

	// Load arrow
	// if( !gArrowTexture.loadFromFile( "arrow.png" ) )
	// {
	// 	printf( "Failed to load arrow texture!\n" );
	// 	success = false;
	// }

	// return success;
}

int main( )
{
	// AGE_Init("AGE Test", SCREEN_WIDTH, SCREEN_HEIGHT, true);
	// AGE_Run
	// AGE_Close();
	AGE_Vector v = {1.f,1.f};
	AGE_Vector v2 = {2.3f,0.f};
	printf("%f\n", AGE_VectorNormalize(v2).X);
	return 0;
}


	// double rot =0;
	// double rotV = 0;
	// char buffer[1024];
	// Timer fpsTimer;
	// Timer capTimer;
	// timer_init(&capTimer);

	// timer_init(&fpsTimer);

	// timer_start(&fpsTimer);
	// int countedFrames = 0;
	// //Start up SDL and create window
	// if(!Initialize())
	// {
	// 	printf( "Failed to initialize!\n" );
	// }
	// else
	// {
	// 	//Load media
	// 	if(!LoadContent())
	// 	{
	// 		printf( "Failed to load media!\n" );
	// 	}
	// 	else
	// 	{	
	// 		//Main loop flag
	// 		bool quit = false;

	// 		//Event handler
	// 		SDL_Event e;

	// 		//Angle of rotation
	// 		double degrees = 0;

	// 		//Flip type
	// 		// SDL_RendererFlip flipType = SDL_FLIP_NONE;

	// 		//While application is running
	// 		while( !quit )
	// 		{				
	// 			timer_start(&capTimer);
	// 			keyboard_update();
	// 			//Handle events on queue
	// 			while(SDL_PollEvent(&e) != 0)
	// 			{
	// 				//User requests quit
	// 				if( e.type == SDL_QUIT )
	// 				{
	// 					quit = true;
	// 				}					
	// 				else if(e.type == SDL_KEYDOWN)
	// 				{
	// 					switch( e.key.keysym.sym )
	// 					{
	// 						// case SDLK_a:
	// 						// degrees -= 60;
	// 						// break;
							
	// 						// case SDLK_d:
	// 						// degrees += 60;
	// 						// break;

	// 						// case SDLK_q:
	// 						// flipType = SDL_FLIP_HORIZONTAL;s
	// 						// break;

	// 						// case SDLK_w:
	// 						// flipType = SDL_FLIP_NONE;
	// 						// break;

	// 						// case SDLK_e:
	// 						// flipType = SDL_FLIP_VERTICAL;
	// 						// break;

	// 						// case SDLK_p:
	// 						// timer_pause(&timer);							
	// 						// break;

	// 						// case SDLK_s:
	// 						// timer_start(&timer);							
	// 						// break;

	// 						// case SDLK_d:
	// 						// timer_stop(&timer);							
	// 						// break;
	// 					}
	// 				}

	// 				mouse_handle_event(&e);
	// 			}
	// 			if(key_is_down(SDL_SCANCODE_LEFT))
	// 			{
	// 				rot-=5;
	// 			}
	// 			float avgFPS = countedFrames / (timer_get_time(&fpsTimer) / 1000.f);
	// 			//Clear screen
	// 			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	// 			SDL_RenderClear( gRenderer );
	// 			SDL_Color textColor = {0,0,0};
	// 			snprintf(buffer, sizeof(buffer), "Left button pressed: %d", Mouse.LeftIsPressed);				
	// 			sprite_load_from_text(&leftButtonText, buffer, textColor);
	// 			snprintf(buffer, sizeof(buffer), "Right button pressed: %d", Mouse.RightIsPressed);				
	// 			sprite_load_from_text(&rightButtonText, buffer, textColor);
	// 			snprintf(buffer, sizeof(buffer), "Middle button pressed: %d", Mouse.MiddleIsPressed);				
	// 			sprite_load_from_text(&middleButtonText, buffer, textColor);
	// 			sprite_render(&leftButtonText, 100, 100, NULL, rot, NULL, SDL_FLIP_NONE);
	// 			sprite_render(&rightButtonText, 100, 200, NULL, rot, NULL, SDL_FLIP_NONE);
	// 			sprite_render(&middleButtonText, 100, 300, NULL, rot, NULL, SDL_FLIP_NONE);
	// 			//Render arrow
	// 			// gArrowTexture.render( ( SCREEN_WIDTH - gArrowTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gArrowTexture.getHeight() ) / 2, NULL, degrees, NULL, flipType );
	// 			// rot += rotV;
	// 			// rotV += 0.2;
	// 			//Update screen
	// 			SDL_RenderPresent( gRenderer );
	// 			++countedFrames;

	// 			int frameTicks = timer_get_time(&capTimer);

	//                if( frameTicks < SCREEN_TICKS_PER_FRAME )
	//                {
	//                    //Wait remaining time
	//                    SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
	//                }
	// 		}
	// 	}
	// }