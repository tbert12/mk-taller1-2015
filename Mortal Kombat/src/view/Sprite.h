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
#include "../model/Renderizable.h"

class Sprite: public Renderizable{
	private:
		int frameActual;
		int cantidadFrames;
		SDL_Rect* spriteFrames;
		LTexture* SpriteSheetTexture;
		Sprite* spriteSiguiente;

	public:
		Sprite(std::string ruta,std::vector<Frame*> frames,SDL_Renderer* Renderer);
		~Sprite();

		virtual void Renderizar();

		void Reset();
		void setRender(SDL_Renderer* Renderer);
		bool Advance();
		bool puedeAvanzar();
		Sprite* getSpriteSiguiente();
		SDL_Rect* getFrame();
		LTexture* getSpriteSheetTexture();
};




#endif /* SRC_VIEW_SPRITE_H_ */
