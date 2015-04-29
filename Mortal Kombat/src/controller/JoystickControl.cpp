/*
 * JoystickControl.cpp
 *
 *  Created on: 28/4/2015
 *      Author: facu
 */

#include "JoystickControl.h"

JoystickControl::JoystickControl(SDL_Event e,Personaje* un_personaje) {
	personaje = un_personaje;
	evento = NULL;
	_Init();
}

void JoystickControl::_Init(){
	joystick =	NULL;
	if(SDL_NumJoysticks() < 1) log("No hay ningun joystick conectado",LOG_WARNING);
	else joystick = SDL_JoystickOpen( 0 );
	if( joystick == NULL ) log(string("No se puede leer el joystick! SDL Error: %s\n", SDL_GetError()),LOG_ERROR);

}

bool JoystickControl::PollEvent(){
	return (SDL_PollEvent( &evento ) != 0);
}

void JoystickControl::JoyPressed(){
	//movimiento del ANALOGICO
	if( evento.type == SDL_JOYAXISMOTION ){
		//En el analogico de la izquierda
		if( evento.jaxis.which == 0 ){
			//X axis motion
			if( evento.jaxis.axis == 0 ){
				//Left of dead zone
				if( evento.jaxis.value < -JOYSTICK_DEAD_ZONE ){
					//IZQUIERDA
				}
				//Right of dead zone
				else if( evento.jaxis.value > JOYSTICK_DEAD_ZONE ){
					//DERECHA
				}
				else{
					//NO SE
				}
			}
			//Y axis motion
			else if( evento.jaxis.axis == 1 ){
				//Below of dead zone
				if( evento.jaxis.value < -JOYSTICK_DEAD_ZONE ){
					//ABAJO
				}
				//Above of dead zone
				else if( evento.jaxis.value > JOYSTICK_DEAD_ZONE ){
					//ARRIBA
				}
				else{
					//NADA
				}
			}
		}
	}
}

JoystickControl::~JoystickControl() {
	SDL_JoystickClose( joystick );
	joystick = NULL;
}

