/*
 * JoystickControl.cpp
 *
 *  Created on: 28/4/2015
 *      Author: facu
 */

#include "JoystickControl.h"

JoystickControl::JoystickControl() {
	joystick =	NULL;
	cant_joystick = SDL_NumJoysticks();
	if(cant_joystick < 1) log("No hay ningun joystick conectado",LOG_WARNING);
	joystick = SDL_JoystickOpen( 0 );
	if( joystick == NULL ) log(string("No se puede leer el joystick! SDL Error: %s\n", SDL_GetError()),LOG_ERROR);

}

JoystickControl::~JoystickControl() {
	SDL_JoystickClose( joystick );
	joystick = NULL;
	cant_joystick = 0;
}

