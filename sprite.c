#include "sprite.h"

void sprite_init(Sprite *sprite)
{
	sprite->texture = NULL;
	sprite->Width = 0;
	sprite->Height = 0;
}

void sprite_destroy(Sprite *sprite)
{	
	sprite_free(sprite);
}

void sprite_free(Sprite *sprite)
{
	if( sprite->texture != NULL )
	{
		SDL_DestroyTexture( sprite->texture );
		sprite->texture = NULL;
		sprite->Width = 0;
		sprite->Height = 0;
	}
}

bool sprite_load(Sprite *sprite, char *path)
{
	sprite_free(sprite);
	
	SDL_Texture *finalTexture = NULL;
	SDL_Surface *loadedSurface = IMG_Load(path);

	if(loadedSurface == NULL)
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
	}
	else
	{

		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        finalTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );

		if( finalTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			sprite->Width = loadedSurface->w;
			sprite->Height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	sprite->texture = finalTexture;
	return finalTexture != NULL;
}

void sprite_set_color(Sprite *sprite, Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod( sprite->texture, red, green, blue );
}

void sprite_set_blendMode(Sprite *sprite, SDL_BlendMode blendMode)
{
	SDL_SetTextureBlendMode( sprite->texture, blendMode );
}
		
void sprite_set_alpha(Sprite *sprite, Uint8 alpha)
{
	SDL_SetTextureAlphaMod(sprite->texture, alpha);
}

void sprite_render(Sprite *sprite, int x, int y, SDL_Rect* clip, double rotation, SDL_Point* origin, SDL_RendererFlip flip)
{
	SDL_Rect renderRect = {x, y, sprite->Width, sprite->Height};

	if(clip!=NULL)
	{
		renderRect.w = clip->w;
		renderRect.h = clip->h;
	}

	SDL_RenderCopyEx(gRenderer, sprite->texture, clip, &renderRect, rotation, origin, flip);
}

bool sprite_load_from_text(Sprite *sprite, char* text, SDL_Color textColor)
{
	sprite_free(sprite);

	SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, text, textColor);
	
	if(textSurface == NULL)
	{
		printf("Text redner error '%s'", TTF_GetError());
	}
	else
	{		
		sprite->texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

		if(sprite->texture == NULL)
		{
			printf("Text render texture from surface error '%s'", text);
		}
		else
		{
			sprite->Width = textSurface->w;
			sprite->Height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return sprite->texture != NULL;
}