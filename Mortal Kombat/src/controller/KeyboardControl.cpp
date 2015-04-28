/*
 * keyboardControl1cpp
 *
 *  Created on: 26/3/2015
 *      Author: tomi
 */

#include "KeyboardControl.h"
#include "../model/DefaultSettings.h"

#include "../model/Personaje.h"

using namespace std;

KeyboardControl::KeyboardControl(SDL_Event e, map<const char*,char> map_comandos, Personaje* un_personaje) {
	personaje = un_personaje;
	quit = false;
	agachado = false;
	keystate = SDL_GetKeyboardState(NULL);
	evento = e;
	mapa_comandos = map_comandos;
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
	} else if(evento.type == SDL_KEYDOWN){
		switch( evento.key.keysym.sym ){
				case  SDLK_UP:
					if (!agachado) personaje->Saltar();
					break;
				case SDLK_DOWN:
					if (!agachado) personaje->Agachar();
					agachado = true;
					break;
				case SDLK_r:
					throw std::runtime_error( "Hay que recargar el archivo JSON." );
					break;



				case SDLK_a:
					personaje->pinaBaja();
					break;
				case SDLK_s:
					if ( (personaje->getSentidoDeMovimiento() > 0 && keystate[SDL_SCANCODE_LEFT])
							or (personaje->getSentidoDeMovimiento() < 0 && keystate[SDL_SCANCODE_RIGHT]) ) {
						personaje->patadaCircular();
					} else personaje->patadaBaja();
					break;
				case SDLK_q:
					personaje->pinaAlta();
					break;
				case SDLK_w:
					personaje->patadaAlta();
					break;
				case SDLK_d:
					if ( agachado ) {
						personaje->cubrirseAgachado();
					} else {
						personaje->cubrirse();
					}
					break;
		}
		/*
		if ( evento.key.keysym.sym == mapa_comandos["pina baja"]) {
			personaje->pinaBaja();
			return;
		} else if ( evento.key.keysym.sym == mapa_comandos["pina alta"] ) {
			personaje->pinaAlta();
			return;
		} else if ( evento.key.keysym.sym == mapa_comandos["patada baja"] ) {
			if ( (personaje->getSentidoDeMovimiento() > 0 && keystate[SDL_SCANCODE_LEFT])
					or (personaje->getSentidoDeMovimiento() < 0 && keystate[SDL_SCANCODE_RIGHT]) ) {
				personaje->patadaCircular();
			} else personaje->patadaBaja();
			return;
		} else if ( evento.key.keysym.sym == mapa_comandos["patada alta"] ) {
			personaje->patadaAlta();
			return;
		} else if ( evento.key.keysym.sym == mapa_comandos["cubrirse"] ) {
			if ( agachado ) {
				personaje->cubrirseAgachado();
			} else {
				personaje->cubrirse();
			}
			return;
		} else if ( evento.key.keysym.sym == mapa_comandos["lanzar arma"] ) {
			personaje->lanzarArma();
			return;
		}*/

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
		}
		/*
		if ( evento.key.keysym.sym == mapa_comandos["cubrirse"] ) {
			personaje->sacarGuardia();
			return;
		}
		*/
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
