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
	keystate = SDL_GetKeyboardState(NULL);
}

bool KeyboardControl::getQuit(){
	return quit;
}

bool KeyboardControl::PollEvent(){
	return (SDL_PollEvent( &evento ) != 0);
}

void KeyboardControl::KeyPressed(){
	if(evento.type == SDL_QUIT){
		quit = true;
	} else if(evento.type == SDL_KEYDOWN and !agachado){
		switch( evento.key.keysym.sym ){
				case SDLK_UP:
					personaje->Saltar();
					break;
				case SDLK_DOWN:
					personaje->Agachar();
					agachado = true;
					break;
				case SDLK_r:
					throw std::runtime_error( "Hay que recargar el archivo JSON." );
					break;
			}
	} else if (evento.type == SDL_KEYUP and evento.type != SDL_MOUSEMOTION){
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
				if (!agachado) personaje->Inicial();
				break;
		}
	} else if (agachado){
		personaje->Agachar();
	}
}

void KeyboardControl::KeyState(){
	//continuous-response keys
	if (agachado) return;
	if (keystate[SDL_SCANCODE_LEFT]) {
		personaje->CaminarIzquierda();
	}
	if(keystate[SDL_SCANCODE_RIGHT]){
		personaje->CaminarDerecha();
	}
}

KeyboardControl::~KeyboardControl() {
	keystate = NULL;
	personaje = NULL;
}
