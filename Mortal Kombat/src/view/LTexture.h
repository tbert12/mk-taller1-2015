/*
 * mundo.h
 *
 *  Created on: 26/3/2015
 *      Author: tomi
 */

#ifndef SRC_VIEW_LTEXTURE_H_
#define SRC_VIEW_LTEXTURE_H_

#include <string>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include "../model/logging.h"
#include "../model/Color.h"

typedef struct Rect_Logico
{
    float x, y;
    float w, h;
} Rect_Logico;

typedef struct Rect_Objeto
{
    int x, y;
    int w, h;
    float w_log,h_log;
} Rect_Objeto;

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture(SDL_Renderer* Renderer);

		//Deallocates memory
		~LTexture();

		// Cambiar el matiz de la textura de acuerdo a ciertos parametros.
		bool cambiarColor(SDL_PixelFormat* format, float, float, float);

		//Loads image at specified path
		bool loadFromFile( std::string path );

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		//renderiza solo fondos
		void renderFondo(Rect_Logico* clip);

		//Renders texture at given point
		void renderObjeto(Rect_Objeto* clip, float x = 0, float y = 0, bool flip = false);


		//Gets image dimensions
		int getWidth();
		int getHeight();

		void setRatio(float ratiox,float ratioy);

		void setDimensionesVentana(int w,int h);
		void renderImagen();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
		float ratio_x_ventana;
		float ratio_y_ventana;
		int w_ventana;
		int h_ventana;

		//The window renderer
		SDL_Renderer* gRenderer;
};


#endif /* SRC_VIEW_LTEXTURE_H_ */
