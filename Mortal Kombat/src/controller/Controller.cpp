/*
 * Controller.cpp
 *
 *  Created on: 29/4/2015
 *      Author: facu
 */

#include "Controller.h"

Controller::Controller(Personaje* un_personaje,Personaje* otro_personaje) {
	personaje_1 = un_personaje;
	personaje_2 = otro_personaje;
	quit = false;
	keystate = SDL_GetKeyboardState(NULL);
	Joystick_1 = NULL;
	Joystick_2 = NULL;
	Teclado = NULL;
	_Init();

}
bool Controller::Quit(){
	return quit;
}

bool Controller::PollEvent(){
	return (SDL_PollEvent( &evento ) != 0);
}

void Controller::_Init(){
	int cant_joy = SDL_NumJoysticks();

	//Si hay dos joystick los uso;
	if (cant_joy >= 2){
		if (personaje_1 != NULL)
			Joystick_1 = new JoystickControl(&evento,0,personaje_1);
		if(personaje_2 != NULL)
			Joystick_2 = new JoystickControl(&evento,1,personaje_2);
	}
	//hay solo un joy entonces es para el jugador uno, el 2 con teclado
	else if (cant_joy == 1){
		if (personaje_1 != NULL)
			Joystick_1 = new JoystickControl(&evento,0,personaje_1);
		if(personaje_2 != NULL)
			Teclado = new KeyboardControl(&evento,personaje_2);
	}
	//no hay joystick conectados, solo teclado
	else{
		if(personaje_1 != NULL)
			Teclado = new KeyboardControl(&evento,personaje_1);
	}

}

void Controller::_JoystickRemoved(){
	printf("JOYSTICK REMOOOOOOVEEEDDD\n");
}

void Controller::Pressed(){
	//evento de salida
	if(evento.type == SDL_QUIT){
		quit = true;
		return;
	}
	//Se retiro el Joystick
	else if(evento.type == SDL_JOYDEVICEREMOVED ){
		printf("removed\n");
		_JoystickRemoved();
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

