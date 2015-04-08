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
}

bool KeyboardControl::getQuit(){
	return quit;
}

void KeyboardControl::KeyPressed(SDL_Event evento){
	if(evento.type == SDL_QUIT){
		quit = true;
	}
	else if(evento.type == SDL_KEYDOWN and evento.key.repeat == 0){

		switch( evento.key.keysym.sym ){
				case SDLK_UP:
					personaje->Saltar();
					break;

				case SDLK_DOWN:
					personaje->Agachar();
					break;

				case SDLK_LEFT:
					if(evento.key.keysym.sym == SDLK_UP){
						//personaje->SaltarIzquierda();
					}
					else{
						personaje->CaminarIzquierda();
					}
					break;

				case SDLK_RIGHT:
					if(evento.key.keysym.sym == SDLK_UP){
						//personaje->SaltarDerecha();
					}
					else{
						personaje->CaminarDerecha();
					}
					break;

				default:
					
					break;
			}
	}
	else if (evento.type == SDL_KEYUP and evento.type != SDL_MOUSEMOTION){
		switch( evento.key.keysym.sym ){
			default:
				personaje->Inicial();
				break;
		}
	}

}

KeyboardControl::~KeyboardControl() {

}
