/*
 * keyboardControl.cpp
 *
 *  Created on: 26/3/2015
 *      Author: tomi
 */

#include "KeyboardControl.h"
#include "../model/Personaje.h"

KeyboardControl::KeyboardControl(Personaje* un_personaje) {
	personaje = un_personaje;
	quit = false;
	keydown = false;
}

bool KeyboardControl::getQuit(){
	return quit;
}

void KeyboardControl::KeyPressed(SDL_Event evento){
	if(evento.type == SDL_QUIT){
		quit = true;
	}
	else if(evento.type == SDL_KEYDOWN){

		switch( evento.key.keysym.sym ){
				case SDLK_UP:
					if (keydown) break;
					personaje->Saltar();
					break;

				case SDLK_DOWN:
					if (keydown) break;
					personaje->Agachar();
					keydown = true;
					break;

				case SDLK_LEFT:
					if(keydown){
						break;
					}
					else{
						personaje->CaminarIzquierda();
					}
					break;

				case SDLK_RIGHT:
					if(keydown){
						break;
					}
					else{
						personaje->CaminarDerecha();
					}
					break;

				default:
					personaje->Inicial();
					break;
			}
	} else if (evento.type == SDL_KEYUP and evento.type != SDL_MOUSEMOTION){
		switch( evento.key.keysym.sym ){
			case SDLK_DOWN:
				keydown = false;
				personaje->Levantarse();
				break;
			case SDLK_LEFT:
				if(keydown) break;
				personaje->Inicial();
				break;
			case SDLK_RIGHT:
				if(keydown) break;
				personaje->Inicial();
				break;
			default:
				personaje->Inicial();
				break;
		}
	}

}

KeyboardControl::~KeyboardControl() {

}
