/*
 * Controller.cpp
 *
 *  Created on: 29/4/2015
 *      Author: facu
 */

#include "Controller.h"

Controller::Controller(Pelea* una_pelea,map<string, int>* mapa_comandos1,map<string, int>* mapa_comandos2,int tiempoMax, int tolerancia) {
	pelea = una_pelea;
	personaje_1 = pelea->getPersonajeUno();
	personaje_2 = pelea->getPersonajeDos();
	quit = false;
	ModoDeJuego = pelea->getModoDeJuego();
	keystate = SDL_GetKeyboardState(NULL);
	Joystick_1 = NULL;
	Joystick_2 = NULL;
	Teclado = NULL;
	SDL_JoystickEventState(SDL_ENABLE);
	_Init(mapa_comandos1,mapa_comandos2,tiempoMax,tolerancia);

}
bool Controller::pausa(){
	if (Teclado != NULL){
		if(Teclado->pause())
			return true;
	}
	if(Joystick_1 != NULL){
		if(Joystick_1->pause())
			return true;
	}
	if(Joystick_2 != NULL){
		if(Joystick_2->pause())
			return true;
	}
	return false;
}

bool Controller::Quit(){
	return quit;
}

bool Controller::PollEvent(){
	SDL_JoystickUpdate();
	return (SDL_PollEvent( &evento ) != 0);
}

void Controller::_Init(map<string, int>* mapa_comandos1,map<string, int>* mapa_comandos2,int tiempoMax, int tolerancia){
	int cant_joy = SDL_NumJoysticks();
	Personaje* p_uno;
	Personaje* p_dos;
	if (ModoDeJuego == MODO_JUGADOR_VS_JUGADOR){
			p_uno = personaje_1;
			p_dos = personaje_2;
	}else if (ModoDeJuego == MODO_JUGADOR_VS_PC){
			cpu = new JugadorCPU(personaje_1, personaje_2);
			p_uno = personaje_1;
			p_dos = NULL;
	} else {
			p_uno = personaje_1;
			p_dos = NULL;
	}


	//Si hay dos joystick los uso;
	if (cant_joy >= 2){
		log("Hay mas de dos joystick conectados, se setean al jugador 1 y 2 .Ademas se crea el teclado para el personaje 1",LOG_DEBUG);
		if (p_uno != NULL){
			comboController = new ComboController(tiempoMax,tolerancia,p_uno->getCombos());
			Joystick_1 = new JoystickControl(&evento,0,p_uno,mapa_comandos1,comboController);
			Teclado = new KeyboardControl(&evento,p_uno,false, NULL);
			if (ModoDeJuego == MODO_ENTRENAMIENTO) Teclado->setPelea(pelea);
		}
		if(p_dos != NULL && ModoDeJuego != MODO_JUGADOR_VS_PC){
			Joystick_2 = new JoystickControl(&evento,1,p_dos,mapa_comandos2,NULL);
		}
	}
	//hay solo un joy entonces es para el jugador uno, el 2 con teclado
	else if (cant_joy == 1){
		log("Hay solo un joystick, se le setea al jugador 1, y el teclado al jugador 2",LOG_WARNING);
		if (p_uno != NULL)
			comboController = new ComboController(tiempoMax,tolerancia,p_uno->getCombos());
			Joystick_1 = new JoystickControl(&evento,0,p_uno,mapa_comandos1,comboController);
		if(p_dos != NULL){
			Teclado = new KeyboardControl(&evento,p_dos,true,NULL);
			if (ModoDeJuego == MODO_ENTRENAMIENTO) Teclado->setPelea(pelea);
		}
	}
	//no hay joystick conectados, solo teclado
	else{
		log("No hay joystick conectado, se setea el teclado al jugador 1",LOG_DEBUG);
		if(p_uno != NULL){
			comboController = new ComboController(tiempoMax,tolerancia,p_uno->getCombos());
			Teclado = new KeyboardControl(&evento,p_uno,true,comboController);
			if (ModoDeJuego == MODO_ENTRENAMIENTO) Teclado->setPelea(pelea);
		}
	}
}

void Controller::_JoystickRemoved(){
}

void Controller::_JoystickAdded(){
}

void Controller::Pressed(){

	cpu->realizarMovimiento();

	//evento de salida
	if(evento.type == SDL_QUIT){
		quit = true;
		return;
	}
	//Se retiro el Joystick
	else if(evento.type == SDL_JOYDEVICEREMOVED ){
		_JoystickRemoved();
	}
	//Se agrego un joys
	else if (evento.type == SDL_JOYDEVICEADDED){
		_JoystickAdded();
	}
	else if (pelea->roundFinalizado() || pelea->peleaFinalizada()){
		return;
	}
	//evento de joystick
	else if(evento.type == SDL_JOYAXISMOTION || evento.type == SDL_JOYBUTTONDOWN){
		//evento en el joystick 1
		if( evento.jaxis.which == 0 ){
			if(Joystick_1 != NULL)
				Joystick_1->JoyPressed();
		}
		//evento en el joystick 2
		else if( evento.jaxis.which == 1 ){
			if(Joystick_2 != NULL)
				Joystick_2->JoyPressed();
		}
	}
	//evento es del teclado
	else if(evento.type == SDL_KEYDOWN){
		if (Teclado != NULL){

			Teclado->KeyPressed();
		}
	}
}

void Controller::KeyState(){
	if (pelea->roundFinalizado() || pelea->peleaFinalizada()){
		return;
	}
	if(Joystick_1 != NULL)
		Joystick_1->JoyState();
	if(Joystick_2 != NULL)
			Joystick_2->JoyState();
	if(Teclado != NULL)
		Teclado->KeyState();
}

int Controller::getSleep(){
	if (Teclado != NULL){
		return Teclado->getSleep();
	}
	return 50000;
}

string Controller::get_stream_teclas(){
	return comboController->get_stream_teclas();
}

bool Controller::checkCombo(){
	return (comboController->checkCombos() > 0 ) ;
}

Controller::~Controller() {
	personaje_1 = NULL;
	personaje_2 = NULL;
	if (Teclado != NULL){
		delete Teclado;
		Teclado = NULL;
	}
	if (Joystick_1 != NULL){
		delete Joystick_1;
		Joystick_1 = NULL;
	}
	if (Joystick_2!= NULL){
		delete Joystick_2;
		Joystick_2 = NULL;
	}
	if (comboController)
		delete comboController;
}



