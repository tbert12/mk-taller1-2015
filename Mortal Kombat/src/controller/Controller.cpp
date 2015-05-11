/*
 * Controller.cpp
 *
 *  Created on: 29/4/2015
 *      Author: facu
 */

#include "Controller.h"

Controller::Controller(Personaje* un_personaje,Personaje* otro_personaje,map<string, int>* mapa_comandos) {
	personaje_1 = un_personaje;
	personaje_2 = otro_personaje;
	quit = false;
	keystate = SDL_GetKeyboardState(NULL);
	Joystick_1 = NULL;
	Joystick_2 = NULL;
	Teclado = NULL;
	SDL_JoystickEventState(SDL_ENABLE);
	_Init(mapa_comandos);
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

void Controller::_Init(map<string, int>* mapa_comandos){
	int cant_joy = SDL_NumJoysticks();

	//Si hay dos joystick los uso;
	if (cant_joy >= 2){
		log("Hay mas de dos joystick conectados, se setean al jugador 1 y 2 .Ademas se crea el teclado para el personaje 1",LOG_DEBUG);
		if (personaje_1 != NULL)
			Joystick_1 = new JoystickControl(&evento,0,personaje_1,mapa_comandos);
			Teclado = new KeyboardControl(&evento,personaje_1,false);
		if(personaje_2 != NULL)
			Joystick_2 = new JoystickControl(&evento,1,personaje_2,mapa_comandos);
	}
	//hay solo un joy entonces es para el jugador uno, el 2 con teclado
	else if (cant_joy == 1){
		log("Hay solo un joystick, se le setea al jugador 1, y el teclado al jugador 2",LOG_WARNING);
		if (personaje_1 != NULL)
			Joystick_1 = new JoystickControl(&evento,0,personaje_1,mapa_comandos);
		if(personaje_2 != NULL)
			Teclado = new KeyboardControl(&evento,personaje_2,true);
	}
	//no hay joystick conectados, solo teclado
	else{
		log("No hay joystick conectado, se setea el teclado al jugador 1",LOG_DEBUG);
		if(personaje_1 != NULL)
			Teclado = new KeyboardControl(&evento,personaje_1,true);
	}
}

void Controller::_JoystickRemoved(){
	printf("JOYSTICK REMOOOOOOVEEEDDD\n");
}

void Controller::_JoystickAdded(){
}

void Controller::Pressed(){

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
	//evento de joystick
	else if(evento.type == SDL_JOYAXISMOTION || evento.type == SDL_JOYBUTTONUP){
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
		if (Teclado != NULL)
			Teclado->KeyPressed();
	}
}

void Controller::KeyState(){
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
}



