#include "AGE/AGE.h"

int MAX_FPS = 60;
int MAX_TICKS_PER_FRAME = 1000 / 60;
int CURRENT_FPS;

SDL_Renderer *gRenderer = NULL;
SDL_Window *gWindow = NULL;

bool VSynced;

bool AGE_Init(const char* windowTitle,int screenWidth, int screenHeight, bool vSync)
{
	bool success = true;
	VSynced = vSync;
	
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

		gWindow = SDL_CreateWindow( windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN );

		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			if(VSynced)
			{
				gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			}
			else
			{
				gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED);
			}

			if( gRenderer == NULL )
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
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

				#ifdef AGE_GRAPHICS_H
					AGE_ListInit(&spriteBatch_age.renderSpritesList, sizeof(renderSprite_age));
					spriteBatch_age.cameraOffset.X = 0;
					spriteBatch_age.cameraOffset.Y = 0;
					
					AGE_ListInit(&spriteBatch_age.renderSpritesList, sizeof(renderSprite_age));
					spriteBatch_age.cameraOffset.X = 0;
					spriteBatch_age.cameraOffset.Y = 0;
				#endif
			}
		}
	}

	return success;
}

void AGE_Run(EventHandle_age eventHandler, UserUpdate_age userUpdate, UserDraw_age userDraw)
{
	AGE_Timer fpsTimer;
	AGE_Timer capTimer;
	AGE_TimerInit(&capTimer);
	AGE_TimerInit(&fpsTimer);
	AGE_TimerStart(&fpsTimer);

	int countedFrames = 0;

	bool quit = false;

	SDL_Event e;

	while( !quit )
	{
		AGE_TimerStart(&capTimer);

		keyboardUpdate_age();

		while(SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}

			eventHandler(&e);
			mouseHandleEvent_age(&e);
		}

		CURRENT_FPS = countedFrames / (AGE_TimerGetTicks(&fpsTimer) / 1000.f);

		userUpdate();
		userDraw();

		++countedFrames;

		int frameTicks = AGE_TimerGetTicks(&capTimer);

        if( frameTicks < MAX_TICKS_PER_FRAME )
        {
            //Wait remaining time
            SDL_Delay( MAX_TICKS_PER_FRAME - frameTicks );
        }
	}
}

void AGE_Close()
{
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