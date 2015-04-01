/*
 * Sprite.h
 *
 *  Created on: 31/3/2015
 *      Author: tomi
 */

#ifndef SRC_VIEW_SPRITE_H_
#define SRC_VIEW_SPRITE_H_

#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>

#include "LTexture.h"
#include "Frame.h"

class Sprite{
	private:
		int frameActual;
		int cantidadFrames;
		SDL_Rect* spriteFrames;
		LTexture* SpriteSheetTexture;
	public:
		Sprite(std::string ruta,Frame** frames,SDL_Renderer* Renderer);
		~Sprite();

		void Reset();
		SDL_Rect* nextFrame();
		LTexture* getSpriteSheetTexture();
};




#endif /* SRC_VIEW_SPRITE_H_ */
