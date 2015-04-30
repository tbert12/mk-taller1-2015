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
	m_vibrar = false;
	mWidth = 0;
	mHeight = 0;
	gRenderer = Renderer;
	ratio_x_ventana = 1;
	ratio_y_ventana = 1;
	w_ventana = 0;
	h_ventana = 0;
	corrimientos = {-5,5,-2,2,-1,1};
	indice_corrimientos = 0;
}

int LTexture::_corrimiento(){
	int corr = corrimientos[indice_corrimientos];
	indice_corrimientos += 1;
	if (indice_corrimientos >= (int)corrimientos.size() ){
		//termino la vibracion
		indice_corrimientos = 0;
		m_vibrar = false;
	}
	return corr;
}

LTexture::~LTexture()
{
	//Liberar
	free();
}

void LTexture::setRatio(float ratiox , float ratioy){
	ratio_x_ventana = ratiox;
	ratio_y_ventana = ratioy;
}

void LTexture::setDimensionesVentana(int w,int h){
	w_ventana = w;
	h_ventana = h;
}

void LTexture::setVibrar(){
	m_vibrar = true;
}



/*
bool LTexture::cambiarColor( SDL_PixelFormat* format, float h_inicial, float h_final, float desplazamiento) {

	bool success = true;

	int mPitch = 0;
	void* mPixels = NULL;

	//Texture is already locked
	if( mPixels != NULL ) {
		log( "Texture is already locked!", LOG_WARNING );
	}
	//Lock texture
	if( SDL_LockTexture( mTexture, NULL, &mPixels, &mPitch ) != 0 ) {
		log( string("Unable to lock texture! SDL_Error: ") + string( SDL_GetError() ), LOG_ERROR );
		success = false;
		return success;
	}



	//Color key pixels
	for( int i = 0; i < pixelCount; ++i ) {

		// Obtengo color RGB del pixel.
		Uint8 r, g, b;
		float h, s, v;
		SDL_GetRGB( pixels[i], format, &r, &g, &b);

		// Transformo de RGB a HSV. Si el hue cae en el rango especificado, se desplaza.
		RGBaHSV(r, g, b, &h, &s, &v);

		bool hayQuePintar = false;
		if ( h >= h_inicial && h <= h_final ) {
			desplazarHue(&h, desplazamiento);
			hayQuePintar = true;
		}

		// Vuelvo a transformar a coordenadas RGB.
		HSVaRGB(h, s, v, &r, &g, &b);

		// Pinto el pixel con el nuevo color.
		if ( hayQuePintar ) {
			Uint32 nuevoColor = SDL_MapRGB( format, r, g, b );
			pixels[i] = nuevoColor;
		}

	}

	//Texture is not locked
	if( mPixels == NULL ) {
		log( "Texture is not locked!", LOG_WARNING );
	}
	//Unlock texture
	else SDL_UnlockTexture( mTexture );

	return success;

}
*/





bool LTexture::loadFromFile( std::string ruta, bool cambiar_color, float h_inicial, float h_final, float desplazamiento ) {

	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* nuevaTexture = NULL;

	//Cargar imagen desde ruta
	SDL_Surface* loadedSurface = IMG_Load( ruta.c_str() );
	if( loadedSurface == NULL ) {
		log( string("No se puede cargar imagen: ") + string( ruta.c_str() ) + string(" SDL_image Error: ") + string(SDL_GetError()),LOG_ERROR);
		return false;
	} else {

		//Color de Imagen
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Dimensiones de imagen
		mWidth = loadedSurface->w;
		mHeight = loadedSurface->h;


		if ( cambiar_color ) {

			//If the surface must be locked
			if( SDL_MUSTLOCK( loadedSurface ) ) {
				//Lock the surface
				SDL_LockSurface( loadedSurface );
			}

			Uint32* pixels = (Uint32*) loadedSurface->pixels;
			for (int i=0; i < ((loadedSurface->pitch)/4 * loadedSurface->h); i++ ) {

				// Obtengo color RGB del pixel.
				Uint8 r, g, b, a;
				float h, s, v;
				SDL_GetRGBA( pixels[i], loadedSurface->format, &r, &g, &b, &a);

				// Transformo de RGB a HSV. Si el hue cae en el rango especificado, se desplaza.
				RGBaHSV(r, g, b, &h, &s, &v);

				bool hayQuePintar = false;
				if ( h >= h_inicial && h <= h_final ) {
					desplazarHue(&h, desplazamiento);
					hayQuePintar = true;
				}

				// Vuelvo a transformar a coordenadas RGB.
				HSVaRGB(h, s, v, &r, &g, &b);

				// Pinto el pixel con el nuevo color.
				if ( hayQuePintar ) {
					Uint32 nuevoColor = SDL_MapRGBA( loadedSurface->format, r, g, b, a );
					pixels[i] = nuevoColor;
				}
			}

			//Unlock surface
			if( SDL_MUSTLOCK( loadedSurface ) ) {
				SDL_UnlockSurface( loadedSurface );
			}
		}

		//Crear textura desde Surface por pixer
		nuevaTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( nuevaTexture == NULL ) {
			log( string("No se puede crear textura desde") + string( ruta.c_str() ),LOG_ERROR);
			return false;
		}

		//Liberar la imagen cargada
		SDL_FreeSurface( loadedSurface );
	}

	//Success
	mTexture = nuevaTexture;
	return true;
}

void LTexture::free() {
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
		gRenderer = NULL;
		ratio_x_ventana = 0;
		ratio_y_ventana = 0;
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

void LTexture::renderObjeto( Rect_Objeto* clip,float x, float y, bool flip)
{
	int corrimiento_x = 0;
	int corrimiento_y = 0;

	if(m_vibrar){
		corrimiento_x = _corrimiento();
		corrimiento_y = corrimiento_x;
	}


	int x_px = (int)(x*ratio_x_ventana + 0.5) + corrimiento_x;
	int y_px = (int)(y*ratio_y_ventana +0.5) + corrimiento_y;

	SDL_Rect Object = { x_px,y_px, mWidth, mHeight};
	SDL_Rect clip_px;
	//Setear tamanio de renderizacion
	if( clip != NULL )
	{
		clip_px = {clip->x, //posicion en pixel horizontal del objeto en la imagen
				clip->y, //posicion en pixel vertical del objeto en la imagen
				clip->w,// ancho en pixel del objeto en la imagen
				clip->h}; //alto en pixel del objeto en la imagen

		Object.w = (int)(clip->w_log*ratio_x_ventana +0.5);	//tamaño logico del objeto por el ratio de ventana
		Object.h = (int)(clip->h_log*ratio_y_ventana +0.5);
	}

	//Renderizar a la pantalla
	SDL_RendererFlip flipType = SDL_FLIP_NONE;
	if(flip)
		flipType = SDL_FLIP_HORIZONTAL;

	SDL_RenderCopyEx( gRenderer, mTexture, &clip_px, &Object,  0 , 0, flipType);
}

void LTexture::renderFondo( Rect_Logico* clip)
{
	int corrimiento_x = 0;
	int corrimiento_y = 0;

	if(m_vibrar){
		corrimiento_x = _corrimiento();
		corrimiento_y = corrimiento_x;
	}

	SDL_Rect camera = { 0,0, w_ventana, h_ventana};
	SDL_Rect clip_px;

	//Setear tamanio de renderizacion
	if( clip != NULL )
	{
		float ratio_x_img = mWidth/clip->w;
		float ratio_y_img =	mHeight/clip->h;

		int ancho_px_ventana = int((w_ventana/ratio_x_ventana)*ratio_x_img + 0.5); //ancho_logico_de_ventana en lo px de la imagen
		int alto_px_ventana = int((h_ventana/ratio_y_ventana)*ratio_y_img + 0.5);

		clip_px = {(int)(clip->x*ratio_x_img  + 0.5), //posicion horizontal de la capa
				(int)(clip->y*ratio_y_img + 0.5), //posicion vertical de la capa
				ancho_px_ventana,//w_ventana , // ancho de la ventana
				alto_px_ventana }; //alto de la ventana

		clip_px.x += corrimiento_x;
		clip_px.y += corrimiento_y;

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
