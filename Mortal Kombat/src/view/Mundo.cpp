/*
 * mundo.cpp
 *
 *  Created on: 26/3/2015
 *      Author: tomi
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

#include "Mundo.h"

LTexture::LTexture()
{
	//Inicializar
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Liberar
	free();
}

bool LTexture::loadFromFile( std::string ruta )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* nuevaTexture = NULL;

	//Cargar imagen desde ruta
	SDL_Surface* loadedSurface = IMG_Load( ruta.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "No se puede cargar imagen %s! SDL_image Error: %s\n", ruta.c_str(), IMG_GetError() );
	}
	else
	{
		//Color de Imagen
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Crear textura desde Surface por pixer
		nuevaTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( nuevaTexture == NULL )
		{
			printf( "No se puede crear textura desde %s! SDL Error: %s\n", ruta.c_str(), SDL_GetError() );
		}
		else
		{
			//Dimensiones de imagen
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Liberar la imagen cargada
		SDL_FreeSurface( loadedSurface );
	}

	//Success
	mTexture = nuevaTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modular textura con RGB
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Setear funcion blending
	SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
	//Modular alpha de textura
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip )
{
	//Setear espacio de renderizacion
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Setear tamanio de renderizacion
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Renderizar a la pantalla
	SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool create_window(int screenWidth, int screenHeight)
{
	//Booleano de inicializacion
	bool success = true;

	//Inicializar SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL no puede inicializar! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Filtrado lineal de textura
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: filtrado lineal de textura no esta habilitado!" );
		}

		//Crear Ventana
		gWindow = SDL_CreateWindow( "World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "La ventana no se puede crear! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Vsync-renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "No se pudo crear la renderizacion! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//render Color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Cargador de PNG
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image no pudo inicializarse! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia(std::string ruta)
{
	//Booleano a devolver
	bool OK = true;

	//Cargar Sprite
	if( !gSpriteSheetTexture.loadFromFile( ruta ) )
	{
		printf( "Error en cargar Sprite\n" );
		OK = false;
	}
	else
	{
		for (int i = 0; i < ANIMATION_IMAGES;i++){
			//Set Sprite Position (+64)
			gSpriteClips[i].x = 64*i;
			gSpriteClips[i].y =    0;
			gSpriteClips[i].w =   64;
			gSpriteClips[i].h =  129;
		}
	}

	return OK;
}

void close_window()
{
	//Liberar imagenes cargadas
	gSpriteSheetTexture.free();

	//Destruir Ventanas
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Cerrar SDL
	IMG_Quit();
	SDL_Quit();
}


