#ifndef MAGIC_H
#define MAGIC_H

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#endif

#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include <stdio.h>

extern SDL_Renderer *gRenderer;
extern SDL_Window *gWindow;

typedef int bool;
enum { false, true };

bool AGE_Init(const char* windowTitle,int screenWidth, int screenHeight, bool vSync);
void AGE_Close();


#endif