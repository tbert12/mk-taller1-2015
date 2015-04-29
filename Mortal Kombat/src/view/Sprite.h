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
#include <stdexcept>
#include <exception>

#include "LTexture.h"
#include "Ventana.h"
#include "Frame.h"
#include "../model/CargarImagenException.h"

class Sprite {
	private:
		int frameActual;
		int cantidadFrames;
		string ruta_archivo;

		bool reverse;
		bool doloop;
		int frameLoop;

		Rect_Objeto* spriteFrames;
		LTexture* SpriteSheetTexture;

	public:
		Sprite(std::string ruta,std::vector<Frame*> frames,Ventana* ventana,float ratio_x, float ratio_y);
		~Sprite();

		bool Advance();
		void Reset();

		// Desplaza un rango de matices del spritesheet.
		void cambiarColor(SDL_PixelFormat*, float, float, float);

		void setLoop(int num_frame);
		void doLoop(bool loop);

		void doReverse(bool Reverse);

		bool ultimoFrame();

		float getAncho();
		float getAlto();


		void setRender(SDL_Renderer* Renderer);
		void render(float x,float y, bool fliped);

		//Rect_Logico* getFrame();
		//LTexture* getSpriteSheetTexture();
};




#endif /* SRC_VIEW_SPRITE_H_ */
