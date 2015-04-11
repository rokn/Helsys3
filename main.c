#include "magic.h"
#include "sprite.h"
#include "timer.h"
#include "keyboard_input.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / 60;

bool Initialize();
bool LoadContent();
void Close();


Sprite spr;

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

TTF_Font *gFont = NULL;

Sprite dots;

bool Initialize()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create *vsynced* renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED);

			if( gRenderer == NULL )
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				if(TTF_Init() == -1)
				{
					printf("SDL_ttf init error");
					success = false;
				}
			}
		}
	}

	return success;
}

bool LoadContent()
{
	//Loading success flag
	bool success = true;

	gFont = TTF_OpenFont("Aver.ttf", 16);
	if(gFont == NULL)
	{
		printf("Font load error 'Aver' Error: %s\n", TTF_GetError());
		success = false;
	}
	// else
	// {
	// 	SDL_Color textColor = {0,0,0};
	// 	sprite_init(&dots);

		// if(!sprite_load_from_text(&dots, "The quick brown fox jumps over the lazy dog", textColor))
		// if(!sprite_load(&dots, "dots.png"))
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

	return success;
}

void Close()
{
	// Free loaded images
	//gArrowTexture.free();	
	sprite_destroy(&dots);

	TTF_CloseFont(gFont);
	gFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	
	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	double rot =0;
	double rotV = 0;
	char buffer[1024];
	Timer fpsTimer;
	Timer capTimer;
	timer_init(&capTimer);

	timer_init(&fpsTimer);

	timer_start(&fpsTimer);
	int countedFrames = 0;
	KeyboardInput keyboard;
	//Start up SDL and create window
	if(!Initialize())
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if(!LoadContent())
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Angle of rotation
			double degrees = 0;

			//Flip type
			// SDL_RendererFlip flipType = SDL_FLIP_NONE;

			//While application is running
			while( !quit )
			{				
				timer_start(&capTimer);
				keyboard_update(&keyboard);
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else if( e.type == SDL_KEYDOWN )
					{
						switch( e.key.keysym.sym )
						{
							// case SDLK_a:
							// degrees -= 60;
							// break;
							
							// case SDLK_d:
							// degrees += 60;
							// break;

							// case SDLK_q:
							// flipType = SDL_FLIP_HORIZONTAL;s
							// break;

							// case SDLK_w:
							// flipType = SDL_FLIP_NONE;
							// break;

							// case SDLK_e:
							// flipType = SDL_FLIP_VERTICAL;
							// break;

							// case SDLK_p:
							// timer_pause(&timer);							
							// break;

							// case SDLK_s:
							// timer_start(&timer);							
							// break;

							// case SDLK_d:
							// timer_stop(&timer);							
							// break;
						}
					}
				}
				if(key_is_held(&keyboard, SDL_SCANCODE_LEFT))
				{
					rot-=5;
				}
				float avgFPS = countedFrames / (timer_get_time(&fpsTimer) / 1000.f);
				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				snprintf(buffer, sizeof(buffer), "FPS : %.f", avgFPS);
				SDL_Color textColor = {0,0,0};
				sprite_load_from_text(&dots, buffer, textColor);	
				sprite_render(&dots, 100, 100, NULL, rot, NULL, SDL_FLIP_NONE);
				//Render arrow
				// gArrowTexture.render( ( SCREEN_WIDTH - gArrowTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gArrowTexture.getHeight() ) / 2, NULL, degrees, NULL, flipType );
				// rot += rotV;
				// rotV += 0.2;
				//Update screen
				SDL_RenderPresent( gRenderer );
				++countedFrames;

				int frameTicks = timer_get_time(&capTimer);

                if( frameTicks < SCREEN_TICKS_PER_FRAME )
                {
                    //Wait remaining time
                    SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
                }
			}
		}
	}

	//Free resources and close SDL
	Close();

	return 0;
}