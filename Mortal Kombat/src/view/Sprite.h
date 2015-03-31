/*
 * Sprite.h
 *
 *  Created on: 31/3/2015
 *      Author: tomi
 */

#ifndef SRC_VIEW_SPRITE_H_
#define SRC_VIEW_SPRITE_H_

#include <SDL2/SDL.h>
#include <string>

#include "Mundo.h"
#include "Frame.h"

class Sprite{
	private:
		int frameActual;
		const int cantidadFrames;
		SDL_Rect spriteFrames[cantidadFrames];
		LTexture SpriteSheetTexture;
	public:
		Sprite(std::string ruta,Frame frames[]);
		~Sprite();

		SDL_Rect nextFrame();
};




#endif /* SRC_VIEW_SPRITE_H_ */
