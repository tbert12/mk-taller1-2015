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
	agachado = false;
}

bool KeyboardControl::getQuit(){
	return quit;
}

void KeyboardControl::KeyPressed(SDL_Event evento){
	if(evento.type == SDL_QUIT){
		quit = true;
	} else if(evento.type == SDL_KEYDOWN and !agachado){
		printf("IF 1\n");
		switch( evento.key.keysym.sym ){
				case SDLK_UP:
					personaje->Saltar();
					break;

				case SDLK_DOWN:
					personaje->Agachar();
					agachado = true;
					break;

				case SDLK_LEFT:
					personaje->CaminarIzquierda();
					break;

				case SDLK_RIGHT:
					personaje->CaminarDerecha();
					break;

				case SDLK_r:
					throw std::runtime_error( "Hay que recargar el archivo JSON." );
					break;
			}
	} else if (evento.type == SDL_KEYUP and evento.type != SDL_MOUSEMOTION){
		printf("IF 2\n");
		switch( evento.key.keysym.sym ){
			case SDLK_DOWN:
				agachado = false;
				personaje->Levantarse();
				break;
			case SDLK_LEFT:
				personaje->Frenar();
				if (!agachado)personaje->Inicial();
				break;
			case SDLK_RIGHT:
				personaje->Frenar();
				if (!agachado)personaje->Inicial();
				break;
			default:
				personaje->Inicial();
				break;
		}
	} else if (agachado){
		printf("IF 3\n");
		personaje->Agachar();
	}
}

KeyboardControl::~KeyboardControl() {

}
