/*
 * keyboardControl.cpp
 *
 *  Created on: 26/3/2015
 *      Author: facu
 */

#include "KeyboardControl.h"
#include "../model/Personaje.h"

KeyboardControl::KeyboardControl(Personaje* un_personaje) {
	personaje = un_personaje;
}

void KeyboardControl::KeyPressed(SDL_Event evento){
	if(evento.type == SDL_QUIT){
		//QUIT
	}
	else if(evento.type == SDL_KEYDOWN){

		switch( evento.key.keysym.sym ){
				case SDLK_UP:
					personaje->Saltar();
					break;

				case SDLK_DOWN:
					personaje->Agachar();
					break;

				case SDLK_LEFT:
					if(evento.key.keysym.sym == SDLK_UP){
						personaje->SaltarIzquierda();
					}
					else{
						personaje->CaminarIzquierda();
					}
					break;

				case SDLK_RIGHT:
					if(evento.key.keysym.sym == SDLK_UP){
						personaje->SaltarDerecha();
					}
					else{
						personaje->CaminarDerecha();
					}
					break;

				default:
					break;
			}
	}
	else{
		//ERROR
	}
}

KeyboardControl::~KeyboardControl() {

}

