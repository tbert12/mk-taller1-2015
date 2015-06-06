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

KeyboardControl::KeyboardControl(SDL_Event* e,Personaje* un_personaje,bool comoJugador,ComboController* comboCon) {
	personaje = un_personaje;
	comboController = comboCon;
	evento = e;
	como_jugador = comoJugador;
	pausa = false;
	returnMenu = false;
	keystate = SDL_GetKeyboardState(NULL);
	sleep = 50000;
	pelea = NULL;
}
bool KeyboardControl::pause(){
	return pausa;
}

bool KeyboardControl::goToMenu(){
	return returnMenu;
}

void KeyboardControl::KeyPressed(){
	switch( evento->key.keysym.sym ){
			case  SDLK_UP:
				if(!como_jugador) return;
				personaje->Saltar();
				if (comboController)
					comboController->sePresiono(ARRIBA);
				break;
			case SDLK_DOWN:
				if(!como_jugador) return;
				personaje->Agachar();
				if (comboController)
					comboController->sePresiono(ABAJO);
				break;
			case SDLK_LEFT:
				if(!como_jugador) return;
				personaje->CaminarIzquierda();
				if (comboController)
					comboController->sePresiono(IZQUIERDA);
				break;
			case SDLK_RIGHT:
				if(!como_jugador) return;
				personaje->CaminarDerecha();
				if (comboController)
					comboController->sePresiono(DERECHA);
				break;
			case SDLK_m:
				returnMenu = true;
				break;
			case SDLK_r:
				if (pelea)
					pelea->reset();
				break;
			case SDLK_a:
				if(!como_jugador) return;
				personaje->pinaBaja();
				if (comboController)
					comboController->sePresiono(PINABAJA);
				break;
			case SDLK_s:
				if(!como_jugador) return;
				personaje->patadaBaja();
				if (comboController)
					comboController->sePresiono(PATADABAJA);
				break;
			case SDLK_q:
				if(!como_jugador) return;
				personaje->pinaAlta();
				if (comboController)
					comboController->sePresiono(PINAALTA);
				break;
			case SDLK_w:
				if(!como_jugador) return;
				personaje->patadaAlta();
				if (comboController)
					comboController->sePresiono(PATADAALTA);
				break;
			case SDLK_d:
				if(!como_jugador) return;
				personaje->cubrirse();
				if (comboController)
					comboController->sePresiono(CUBRIR);
				break;
			case SDLK_c:
				if(!como_jugador) return;
				personaje->poder2();
				break;
			case SDLK_z:
				if(!como_jugador) return;
				personaje->poder1();
				break;
			case SDLK_x:
				if(!como_jugador) return;
				personaje->toma1();
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
	if(comboController->checkCombos() > 0){
		//combo a jugador
	}
}

int KeyboardControl::getSleep(){

	return sleep;
}

void KeyboardControl::KeyState(){
	//si no esta como jugador no verifica nada
	if(!como_jugador) return;

	if (comboController)
		comboController->Update();

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
