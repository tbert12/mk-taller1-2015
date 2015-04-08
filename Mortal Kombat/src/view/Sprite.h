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
#include <vector>

#include "LTexture.h"
#include "Frame.h"
#include "../model/logging.h"

class Sprite {
	private:
		int frameActual;
		int cantidadFrames;
		SDL_Rect* spriteFrames;
		LTexture* SpriteSheetTexture;
		Sprite* spriteSiguiente;

	public:
		Sprite(std::string ruta,std::vector<Frame*> frames,SDL_Renderer* Renderer);
		~Sprite();

		void setSpriteSiguiente(Sprite* nextsprite);
		void Reset();
		void setRender(SDL_Renderer* Renderer);
		bool Advance();
		bool puedeAvanzar();
		void render(int x,int y);
		Sprite* getSpriteSiguiente();
		SDL_Rect* getFrame();
		LTexture* getSpriteSheetTexture();
};




#endif /* SRC_VIEW_SPRITE_H_ */
