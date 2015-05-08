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

KeyboardControl::KeyboardControl(SDL_Event* e,Personaje* un_personaje) {
	personaje = un_personaje;
	evento = e;
	pausa = false;
	keystate = SDL_GetKeyboardState(NULL);
	sleep = 50000;
}
bool KeyboardControl::pause(){
	return pausa;
}
void KeyboardControl::KeyPressed(){
	switch( evento->key.keysym.sym ){
			case  SDLK_UP:
				personaje->Saltar();
				break;
			case SDLK_DOWN:
				personaje->Agachar();
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
			case SDLK_a:
				personaje->pinaBaja();
				break;
			case SDLK_s:
				personaje->patadaBaja();
				break;
			case SDLK_q:
				personaje->pinaAlta();
				break;
			case SDLK_w:
				personaje->patadaAlta();
				break;
			case SDLK_d:
				personaje->cubrirse();
				break;
			case SDLK_z:
				personaje->lanzarObjeto();
				break;
			case SDLK_p:
				pausa = !pausa;
				break;
			case SDLK_F1:
				sleep+=10000;
				break;
			case SDLK_F2:
				sleep-=10000;
				if (sleep < 0) sleep = 0;
				break;
		}
}

int KeyboardControl::getSleep(){

	return sleep;
}

void KeyboardControl::KeyState(){
	//Teclas que deben estar apretadas
	if ((!keystate[SDL_SCANCODE_RIGHT] && (personaje->getSentidoDeMovimiento() > 0))|| (!keystate[SDL_SCANCODE_LEFT] && (personaje->getSentidoDeMovimiento() < 0)) )
		personaje->Frenar();

	if(!keystate[SDL_SCANCODE_DOWN])
		personaje->Levantarse();

	if(!keystate[SDL_SCANCODE_D])
		personaje->dejarDeCubrirse();
}

KeyboardControl::~KeyboardControl() {
	keystate = NULL;
	personaje = NULL;
}
