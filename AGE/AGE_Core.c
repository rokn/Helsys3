#include "AGE.h"
#include "AGE_Graphics.h"
#include "AGE_Input.h"

int MAX_FPS;
int MAX_TICKS_PER_FRAME;
int CURRENT_FPS;

AGE_Rect AGE_WindowRect;

SDL_Renderer *gRenderer = NULL;
SDL_Window *gWindow = NULL;

Uint32 lastUpdate;

bool quit;

void GoBorderless(SDL_Window*, SDL_Rect*);

bool VSynced;

bool AGE_Init(const char* windowTitle,int screenWidth, int screenHeight, bool vSync)
{
	bool success = true;
	VSynced = vSync;
	AGE_SetMaxFPS(60);
	
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

		gWindow = SDL_CreateWindow( windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN |SDL_WINDOW_FULLSCREEN);
		AGE_WindowRect = (AGE_Rect){0,0,screenWidth,screenHeight};

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

				AGE_ListInit(&spriteBatch_age.renderSpritesList, sizeof(renderSprite_age));
				spriteBatch_age.cameraOffset.X = 0;
				spriteBatch_age.cameraOffset.Y = 0;
				
				AGE_ListInit(&spriteBatch_age.renderSpritesList, sizeof(renderSprite_age));
				spriteBatch_age.cameraOffset.X = 0;
				spriteBatch_age.cameraOffset.Y = 0;

				AGE_Vector zeroV = {0.0f, 0.0f};
				AGE_DrawSetCameraTransform(zeroV);
				AGE_ViewRect.Width = AGE_WindowRect.Width;
				AGE_ViewRect.Height = AGE_WindowRect.Height;
			}
		}
	}

	return success;
}

void AGE_Exit()
{
	quit = true;
}

void AGE_SetWindowSize(int Width,int Height)
{
	SDL_SetWindowSize(gWindow, Width, Height);
}

void AGE_Run(EventHandle_age eventHandler, UserUpdate_age userUpdate, UserDraw_age userDraw)
{
	AGE_Timer fpsTimer;
	AGE_Timer capTimer;
	AGE_TimerInit(&capTimer);
	AGE_TimerInit(&fpsTimer);
	AGE_TimerStart(&fpsTimer);

	quit = false;
	int countedFrames = 0;	

	SDL_Event e;

	while( !quit )
	{
		if(!VSynced)
		{
			AGE_TimerStart(&capTimer);
		}

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
		lastUpdate = SDL_GetTicks();
		userDraw();		

		++countedFrames;

		if(!VSynced)
		{
			int frameTicks = AGE_TimerGetTicks(&capTimer);

	        if( frameTicks < MAX_TICKS_PER_FRAME )
	        {
	            //Wait remaining time
	            SDL_Delay( MAX_TICKS_PER_FRAME - frameTicks );
	        }
    	}    	    	
	}
}

void AGE_SetMaxFPS(int maxFps)
{
	MAX_FPS = maxFps;
	if(MAX_FPS>1000)
	{
		MAX_FPS = 1000;
	}
	MAX_TICKS_PER_FRAME = 1000/MAX_FPS;
}

double AGE_DeltaSecondsGet()
{
	Uint32 milliSeconds = AGE_DeltaMilliSecondsGet();
	double result = milliSeconds / 1000.f;
	return result;
}

Uint32 AGE_DeltaMilliSecondsGet()
{
	Uint32 curr = SDL_GetTicks();
	Uint32 result = curr - lastUpdate;
	if(result<1)
	{
		result = 1;
	}
	return result;
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

void AGE_FullScreenBorderless()
{
	SDL_Rect oldRect = {0,0, AGE_WindowRect.Width, AGE_WindowRect.Height};
    GoBorderless(gWindow, &oldRect);    
}

void GoBorderless(SDL_Window* window, SDL_Rect* oldBounds)
{
    if(SDL_GetWindowFlags(window) & SDL_WINDOW_BORDERLESS)
    {
        SDL_SetWindowBordered(window, SDL_TRUE);
        SDL_SetWindowSize(window, oldBounds->w, oldBounds->h);
        SDL_SetWindowPosition(window, oldBounds->x, oldBounds->y);

        AGE_WindowRect.Width = oldBounds->w;
		AGE_WindowRect.Height = oldBounds->h;
		AGE_ViewRect.Width = AGE_WindowRect.Width;
		AGE_ViewRect.Height = AGE_WindowRect.Height;

        return oldBounds;
    }
    else
    {
        SDL_Rect curBounds;
        SDL_GetWindowPosition(window, &curBounds.x, &curBounds.y);
        SDL_GetWindowSize(window, &curBounds.w, &curBounds.h);

        int idx = SDL_GetWindowDisplayIndex(window);
        SDL_Rect bounds;
        SDL_GetDisplayBounds(idx, &bounds);
        SDL_SetWindowBordered(window, SDL_FALSE);
        SDL_SetWindowPosition(window, bounds.x, bounds.y);
        SDL_SetWindowSize(window, bounds.w, bounds.h);

		AGE_WindowRect.Width = curBounds.w;
		AGE_WindowRect.Height = curBounds.h;
		AGE_ViewRect.Width = AGE_WindowRect.Width;
		AGE_ViewRect.Height = AGE_WindowRect.Height;

        return curBounds;
    }
}

