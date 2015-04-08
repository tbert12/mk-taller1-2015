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


//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture(SDL_Renderer* Renderer);

		//Deallocates memory
		~LTexture();

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

		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL );

		//Gets image dimensions
		int getWidth();
		int getHeight();

		void setRelacionPixel(float p_a_l);

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
		float m_relacion_pixel;

		//The window renderer
		SDL_Renderer* gRenderer;
};


#endif /* SRC_VIEW_LTEXTURE_H_ */
