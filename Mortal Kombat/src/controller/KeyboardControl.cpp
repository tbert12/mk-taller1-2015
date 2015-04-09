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
	printf("KeyPressed\n");
	if(evento.type == SDL_QUIT){
		quit = true;
	} else if(evento.type == SDL_KEYDOWN and !keydown){
		printf("1er IF\n");
		switch( evento.key.keysym.sym ){
				case SDLK_UP:
					personaje->Saltar();
					break;

				case SDLK_DOWN:
					personaje->Agachar();
					keydown = true;
					break;

				case SDLK_LEFT:
					personaje->CaminarIzquierda();
					break;

				case SDLK_RIGHT:
					personaje->CaminarDerecha();
					break;

				default:
					personaje->Inicial();
					break;
			}
	} else if (evento.type == SDL_KEYUP){
		printf("2do IF\n");
		switch( evento.key.keysym.sym ){
			case SDLK_DOWN:
				printf(" -Levantarse\n");
				keydown = false;
				personaje->Levantarse();
				break;
			case SDLK_LEFT:
				printf(" -Izquierda\n");
				break;
			case SDLK_RIGHT:
				printf("-Derecha\n");
				break;
			case SDLK_UP:
				printf(" -Arriba\n");
				break;
			default:
				printf(" -Inicial\n");
				if (!keydown) personaje->Inicial();
				break;
		}
	} else {
		printf("3er IF (Frenar)\n");
		if (!keydown){
			personaje->Frenar();
		}
	}

}

KeyboardControl::~KeyboardControl() {

}
