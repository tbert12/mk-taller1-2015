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

KeyboardControl::KeyboardControl(SDL_Event* e,Personaje* un_personaje,bool comoJugador,int tiempoMax,int tolerancia) {
	personaje = un_personaje;
	comboController = new ComboController(tiempoMax,tolerancia,personaje->getCombos());
	evento = e;
	como_jugador = comoJugador;
	pausa = false;
	keystate = SDL_GetKeyboardState(NULL);
	sleep = 50000;
	pelea = NULL;
}
bool KeyboardControl::pause(){
	return pausa;
}
void KeyboardControl::KeyPressed(){
	switch( evento->key.keysym.sym ){
			case  SDLK_UP:
				if(!como_jugador) return;
				personaje->Saltar();
				//comboController->sePresiono(Movimientos[SALTAR]);
				break;
			case SDLK_DOWN:
				if(!como_jugador) return;
				personaje->Agachar();
				//comboController->sePresiono(Movimientos[AGACHAR]);
				break;
			case SDLK_LEFT:
				if(!como_jugador) return;
				personaje->CaminarIzquierda();
				//comboController->sePresiono(Movimientos[IZQUIERDA]);
				break;
			case SDLK_RIGHT:
				if(!como_jugador) return;
				personaje->CaminarDerecha();
				//comboController->sePresiono(Movimientos[DERECHA]);
				break;
			case SDLK_m:
				throw std::runtime_error( "Hay que recargar el archivo JSON." );
				break;
			case SDLK_r:
				if (pelea)
					pelea->reset();
				break;
			case SDLK_a:
				if(!como_jugador) return;
				personaje->pinaBaja();
				//comboController->sePresiono(Movimientos[PINABAJA]);
				break;
			case SDLK_s:
				if(!como_jugador) return;
				personaje->patadaBaja();
				//comboController->sePresiono(Movimientos[PATADABAJA]);
				break;
			case SDLK_q:
				if(!como_jugador) return;
				personaje->pinaAlta();
				break;
			case SDLK_w:
				if(!como_jugador) return;
				personaje->patadaAlta();
				break;
			case SDLK_d:
				if(!como_jugador) return;
				personaje->cubrirse();
				break;
			case SDLK_z:
				if(!como_jugador) return;
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
	//si no esta como jugador no verifica nada
	if(!como_jugador) return;

	//Teclas que deben estar apretadas
	if ((!keystate[SDL_SCANCODE_RIGHT] && (personaje->getSentidoDeMovimiento() > 0))|| (!keystate[SDL_SCANCODE_LEFT] && (personaje->getSentidoDeMovimiento() < 0)) )
		personaje->Frenar();

	if(!keystate[SDL_SCANCODE_DOWN])
		personaje->Levantarse();

	if(!keystate[SDL_SCANCODE_D])
		personaje->dejarDeCubrirse();
}

void KeyboardControl::setPelea(Pelea* una_pelea){
	pelea = una_pelea;
}

KeyboardControl::~KeyboardControl() {
	if (comboController) delete comboController;
	keystate = NULL;
	personaje = NULL;
}
