#ifndef MAGIC_H
#define MAGIC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

extern SDL_Renderer *gRenderer;
extern TTF_Font *gFont;

typedef int bool;
enum { false, true };

#endif