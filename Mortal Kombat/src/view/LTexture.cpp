/*
 * mundo.cpp
 *
 *  Created on: 26/3/2015
 *      Author: tomi
 */

#include "LTexture.h"

//Walking animation
//const int ANIMATION_IMAGES = 9;
//SDL_Rect gSpriteClips[ ANIMATION_IMAGES ];
//LTexture gSpriteSheetTexture;

LTexture::LTexture(SDL_Renderer* Renderer)
{
	//Inicializar LTexture
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	gRenderer = Renderer;
	ratio_x = 1;
	ratio_y = 1;
	w_ventana = 0;
	h_ventana = 0;
}

LTexture::~LTexture()
{
	//Liberar
	free();
}

void LTexture::setRatio(float ratiox , float ratioy){
	ratio_x = ratiox;
	ratio_y = ratioy;
}

void LTexture::setDimensionesVentana(int w,int h){
	w_ventana = w;
	h_ventana = h;
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

void LTexture::renderObjeto( SDL_Rect* clip,float x, float y)
{
	int x_px = (int)x*ratio_x;
	int y_px = (int)y*ratio_y;

	SDL_Rect camera = { x_px,y_px, mWidth, mHeight};
	SDL_Rect clip_px;
	//Setear tamanio de renderizacion
	if( clip != NULL )
	{
		clip_px = {clip->x*ratio_x, //posicion horizontal de la capa
				clip->y*ratio_y, //posicion vertical de la capa
				clip->w*ratio_x, // ancho del objeto
				clip->h*ratio_y }; //alto del objeto

		camera.w = clip_px.w;//Siempre el tamaño de la ventana
		camera.h = clip_px.h;
	}

	//Renderizar a la pantalla
	SDL_RenderCopy( gRenderer, mTexture, &clip_px, &camera );
}



void LTexture::renderFondo( SDL_Rect* clip)
{

	SDL_Rect camera = { 0,0, mWidth, mHeight};
	SDL_Rect clip_px;
	//Setear tamanio de renderizacion
	if( clip != NULL )
	{
		clip_px = {clip->x*ratio_x - w_ventana/2, //posicion horizontal de la capa
				clip->y*ratio_y, //posicion vertical de la capa
				w_ventana , // ancho de la ventana
				h_ventana }; //alto de la ventana

		camera.w = w_ventana;//Siempre el tamaño de la ventana
		camera.h = h_ventana;
	}

	//Renderizar a la pantalla
	SDL_RenderCopy( gRenderer, mTexture, &clip_px, &camera );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}


