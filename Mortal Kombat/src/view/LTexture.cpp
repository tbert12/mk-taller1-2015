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
		log( string("No se puede cargar imagen %s! SDL_image Error: %s\n", ruta.c_str()),LOG_ERROR);
	}
	else
	{
		//Color de Imagen
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Crear textura desde Surface por pixer
		nuevaTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( nuevaTexture == NULL )
		{
			log( string("No se puede crear textura desde %s!", ruta.c_str()),LOG_ERROR);
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
		gRenderer = NULL;
		ratio_x = 0;
		ratio_y = 0;
		w_ventana = 0;
		h_ventana = 0;
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

void LTexture::renderObjeto( Rect_Logico* clip,float x, float y, bool flip)
{
	int x_px = (int)(x*ratio_x);
	int y_px = (int)(y*ratio_y);

	SDL_Rect Object = { x_px,y_px, mWidth, mHeight};
	SDL_Rect clip_px;
	//Setear tamanio de renderizacion
	if( clip != NULL )
	{
		//El + 0.5 es el casteo que usa en C++
		//Si se usa la librea std::round. HACE LO MISMO!. (StackOverFlow)
		clip_px = {(int)(clip->x*ratio_x + 0.5), //posicion horizontal del objeto
				(int)(clip->y*ratio_y + 0.5), //posicion vertical del objeto
				(int)(clip->w*ratio_x + 0.5), // ancho del objeto
				(int)(clip->h*ratio_y + 0.5) }; //alto del objeto

		//Cuanto lo tengo que estirar dependiendo el tamano de a pantall?
		//Ahora lo estoy aumentando 40 pixeles en y, y 20 en x, para que vean
		int nuevo_h_estirado = clip_px.h + 40;
		int nuevo_w_estirado = clip_px.w + 20;

		Object.x = Object.x - nuevo_w_estirado + clip_px.w;
		Object.y = Object.y - nuevo_h_estirado + clip_px.h;
		Object.w = nuevo_w_estirado;//Siempre el tamaño de la ventana
		Object.h = nuevo_h_estirado;
	}

	//Renderizar a la pantalla
	SDL_RendererFlip flipType = SDL_FLIP_NONE;
	if(flip)
		flipType = SDL_FLIP_HORIZONTAL;

	SDL_RenderCopyEx( gRenderer, mTexture, &clip_px, &Object,  0 , 0, flipType);
}

void LTexture::renderFondo( Rect_Logico* clip)
{
	SDL_Rect camera = { 0,0, w_ventana, h_ventana};
	SDL_Rect clip_px;

	//Setear tamanio de renderizacion
	if( clip != NULL )
	{
		float ratio_x_img = mWidth/clip->w;
		float ratio_y_img =	mHeight/clip->h;

		int ancho_px_ventana = int((w_ventana/ratio_x)*ratio_x_img + 0.5); //ancho_logico_de_ventana en lo px de la imagen
		int alto_px_ventana = int((h_ventana/ratio_y)*ratio_y_img + 0.5);

		clip_px = {(int)(clip->x*ratio_x_img  + 0.5), //posicion horizontal de la capa
				(int)(clip->y*ratio_y_img + 0.5), //posicion vertical de la capa
				ancho_px_ventana,//w_ventana , // ancho de la ventana
				alto_px_ventana }; //alto de la ventana


		int ancho = (int)(clip->w*ratio_x_img + 0.5);
		if(clip_px.x > (ancho - ancho_px_ventana))clip_px.x = ancho - ancho_px_ventana;
		if(clip_px.x <0)clip_px.x = 0;

		camera.w = w_ventana;//Siempre el tamaño de la ventana
		camera.h = h_ventana;
	}

	//Renderizar a la pantalla
	SDL_RenderCopy( gRenderer, mTexture, &clip_px, &camera );
}

void LTexture::renderImagen(){
	SDL_Rect camera = { 0,0, w_ventana, h_ventana};
	SDL_Rect clip = {0,0,w_ventana,h_ventana};
	SDL_RenderCopy( gRenderer, mTexture, &clip, &camera);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}
