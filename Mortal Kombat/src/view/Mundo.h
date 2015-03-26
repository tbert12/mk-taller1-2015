/*
 * mundo.h
 *
 *  Created on: 26/3/2015
 *      Author: tomi
 */

#ifndef SRC_VIEW_MUNDO_H_
#define SRC_VIEW_MUNDO_H_

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

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

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//Starts up SDL and creates window
bool create_window(int screenWidth, int screenHeight);

//Loads media
bool loadMedia(std::string ruta);

//Frees media and shuts down SDL
void close_window();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Walking animation
const int ANIMATION_IMAGES = 9;
SDL_Rect gSpriteClips[ ANIMATION_IMAGES ];
LTexture gSpriteSheetTexture;



#endif /* SRC_VIEW_MUNDO_H_ */