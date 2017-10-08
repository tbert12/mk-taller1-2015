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
#include "LSound.h"
#include "../model/CargarImagenException.h"

class Sprite {
	private:
		int frameActual;
		int cantidadFrames;

		bool reproducioSonido;

		bool reverse;
		bool doloop;
		int frameLoop;
		int m_pong;
		int m_fullpong;

		bool frezee;
		int frezeeTime;
		int frezeeCount;
		int frezeeFrame;

		LSound* sonido=NULL;
		int frameSound;

		Rect_Objeto* spriteFrames;
		LTexture* SpriteSheetTexture;

	public:
		Sprite(std::string ruta,std::vector<Frame*> frames,Ventana* ventana,float ratio_x, float ratio_y, bool cambiar_color = false, float h_inicial = 0, float h_final = 0, float desplazamiento = 0, LSound* sonido_accion = NULL);
		~Sprite();

		bool Advance();
		void Reset();
		void hardReset();

		void setLoop(int num_frame);
		void setFrezeeFrame(int frame,int time);
		void freezeSprite();
		void doPongIn(int pong);
		void doFullPong();
		void doLoop(bool loop);
		void doReverse(bool Reverse);
		void retrocederFrames(int frames);
		void setSoundIn(int index_frame);
		void playSound();

		bool inFrezee();
		bool ultimoFrame();
		bool proxFrameUltimo();
		bool primerFrame();
		bool inLoop();
		bool loop();
		bool inReverse();

		float getAncho();
		float getAlto();

		void vibrar();
		void setRender(SDL_Renderer* Renderer);
		void render(float x,float y, bool fliped);
		void renderSpecialText();

		//PARA TESTEO
		LTexture* RectanguloTest1;
		LTexture* RectanguloTest2;
		void RENDERCOLISIONTEST(float x, float y, bool fliped,Rect_Logico* rectanguloAtaque,Rect_Logico* b);

		//Rect_Logico* getFrame();
		//LTexture* getSpriteSheetTexture();
};




#endif /* SRC_VIEW_SPRITE_H_ */
