/*
 * keyboardControl1.cpp
 *
 *  Created on: 26/3/2015
 *      Author: tomi
 */

#include "KeyboardControl1.h"

#include "../model/Personaje.h"

KeyboardControl1::KeyboardControl1(Personaje* un_personaje) {
	personaje = un_personaje;
	quit = false;
	agachado = false;
	keystate = SDL_GetKeyboardState(NULL);
}

bool KeyboardControl1::getQuit(){
	return quit;
}

bool KeyboardControl1::PollEvent(){
	return (SDL_PollEvent( &evento ) != 0);
}

void KeyboardControl1::KeyPressed(){
	if(evento.type == SDL_QUIT){
		quit = true;
	} else if(evento.type == SDL_KEYDOWN){
		switch( evento.key.keysym.sym ){
				case SDLK_UP:
					if (!agachado) personaje->Saltar();
					break;
				case SDLK_DOWN:
					if (!agachado) personaje->Agachar();
					agachado = true;
					break;
				case SDLK_r:
					throw std::runtime_error( "Hay que recargar el archivo JSON." );
					break;
				case SDLK_h:
					personaje->pinaBaja();
					break;
				case SDLK_j:
					personaje->pinaAlta();
					break;
				case SDLK_k:
					if ( (personaje->getSentidoDeMovimiento() > 0 && keystate[SDL_SCANCODE_LEFT])
							or (personaje->getSentidoDeMovimiento() < 0 && keystate[SDL_SCANCODE_RIGHT]) ) {
						personaje->patadaCircular();
					} else personaje->patadaBaja();
					break;
				case SDLK_l:
					personaje->patadaAlta();
					break;
				case SDLK_RCTRL:
					if ( agachado ) {
						personaje->cubrirseAgachado();
					} else {
						personaje->cubrirse();
					}
					break;

		}
	} else if (evento.type == SDL_KEYUP){
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
			case SDLK_UP:
				if (!agachado) personaje->Inicial();
				break;
			case SDLK_RCTRL:
				personaje->sacarGuardia();
				break;
		}

	} /*else if (agachado){
		personaje->Agachar();
	}
	*/
}

void KeyboardControl1::KeyState(){
	//continuous-response keys
	if (agachado) return;
	if (keystate[SDL_SCANCODE_LEFT]) {
		personaje->CaminarIzquierda();
	}
	if(keystate[SDL_SCANCODE_RIGHT]){
		personaje->CaminarDerecha();
	}
}

KeyboardControl1::~KeyboardControl1() {
	keystate = NULL;
	personaje = NULL;
}
