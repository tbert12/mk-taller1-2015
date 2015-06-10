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

KeyboardControl::KeyboardControl(SDL_Event* e,Personaje* un_personaje,bool comoJugador,ComboController* comboCon,Pelea* una_pelea) {
	personaje = un_personaje;
	comboController = comboCon;
	if (personaje)
		combosPosibles = personaje->getCombos();
	evento = e;
	como_jugador = comoJugador;
	pausa = false;
	returnMenu = false;
	keystate = SDL_GetKeyboardState(NULL);
	sleep = 50000;
	pelea = una_pelea;
}
bool KeyboardControl::pause(){
	return pausa;
}

bool KeyboardControl::goToMenu(){
	return returnMenu;
}

void KeyboardControl::KeyPressed(){
	if (evento->key.repeat) {
		return;
	}
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
				if (comboController){
					int accion;
					if (!personaje->getFlipState())
						accion = IZQUIERDA;
					else accion = DERECHA;
					comboController->sePresiono(accion);
				}
				break;
			case SDLK_RIGHT:
				if(!como_jugador) return;
				personaje->CaminarDerecha();
				if (comboController){
					int accion;
					if (!personaje->getFlipState())
						accion = DERECHA;
					else accion = IZQUIERDA;
					comboController->sePresiono(accion);
				}
				break;
			case SDLK_m:
				returnMenu = true;
				return;
				break;
			case SDLK_r:
				if (pelea->modoDeJuego() == MODO_ENTRENAMIENTO)
					pelea->reset();
				return;
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

	if(comboController){
		int combo_a_realizar =  comboController->checkCombos();
		if (combo_a_realizar >= 0){
			switch (combo_a_realizar){
				case PODER1:
					personaje->poder1();
					break;
				case PODER2:
					personaje->poder2();
					break;
			}
		}
		if (pelea->inFinishHim()){
			int fatality_a_realizar =  comboController->checkFatalities();
			switch (fatality_a_realizar){
				case FATALITY1:
					personaje->fatality1(pelea->getContrincante(personaje));
					pelea->setFatality();
					break;
			}
		}
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
	if (keystate[SDL_SCANCODE_UP])
			personaje->Saltar();

	if ((!keystate[SDL_SCANCODE_RIGHT] && (personaje->getSentidoDeMovimiento() > 0))|| (!keystate[SDL_SCANCODE_LEFT] && (personaje->getSentidoDeMovimiento() < 0)) )
		personaje->Frenar();

	if(!keystate[SDL_SCANCODE_DOWN])
		personaje->Levantarse();

	if(!keystate[SDL_SCANCODE_D])
		personaje->dejarDeCubrirse();
}

KeyboardControl::~KeyboardControl() {
	if (comboController) delete comboController;
	keystate = NULL;
	personaje = NULL;
}
