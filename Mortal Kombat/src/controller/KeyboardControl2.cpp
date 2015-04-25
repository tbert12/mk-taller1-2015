/*
 * keyboardControl2.cpp
 *
 *  Created on: 26/3/2015
 *      Author: tomi
 */

#include "KeyboardControl2.h"

#include "../model/Personaje.h"

KeyboardControl2::KeyboardControl2(Personaje* un_personaje) {
	personaje = un_personaje;
	quit = false;
	agachado = false;
	keystate = SDL_GetKeyboardState(NULL);
}

bool KeyboardControl2::getQuit(){
	return quit;
}

bool KeyboardControl2::PollEvent(){
	return (SDL_PollEvent( &evento ) != 0);
}

void KeyboardControl2::KeyPressed(){
	if(evento.type == SDL_QUIT){
		quit = true;
	} else if(evento.type == SDL_KEYDOWN and !agachado){
		switch( evento.key.keysym.sym ){
				case SDLK_w:
					personaje->Saltar();
					break;
				case SDLK_s:
					personaje->Agachar();
					agachado = true;
					break;
			}
	} else if (evento.type == SDL_KEYUP){
		switch( evento.key.keysym.sym ){
			case SDLK_s:
				agachado = false;
				personaje->Levantarse();
				break;
			case SDLK_a:
				personaje->Frenar();
				if (!agachado)personaje->Inicial();
				break;
			case SDLK_d:
				personaje->Frenar();
				if (!agachado)personaje->Inicial();
				break;
			case SDLK_w:
				if (!agachado) personaje->Inicial();
				break;
		}
	} else if (agachado){
		personaje->Agachar();
	}
}

void KeyboardControl2::KeyState(){
	//continuous-response keys
	if (agachado) return;
	if (keystate[SDL_SCANCODE_A]) {
		personaje->CaminarIzquierda();
	}
	if(keystate[SDL_SCANCODE_D]){
		personaje->CaminarDerecha();
	}
}

KeyboardControl2::~KeyboardControl2() {
	keystate = NULL;
	personaje = NULL;
}
