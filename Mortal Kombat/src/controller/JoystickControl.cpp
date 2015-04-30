/*
 * JoystickControl.cpp
 *
 *  Created on: 28/4/2015
 *      Author: facu
 */

#include "JoystickControl.h"

JoystickControl::JoystickControl(SDL_Event* e,int id_joystick,Personaje* un_personaje) {
	personaje = un_personaje;
	evento = e;
	_Init(id_joystick);
}

void JoystickControl::_Init(int id){
	joystick =	NULL;
	if(SDL_NumJoysticks() < id +1) log(string("No se puede abrir el joystick con ID :"),LOG_ERROR);
	else joystick = SDL_JoystickOpen( id );
	if( joystick == NULL ) log(string("No se puede leer el joystick! SDL Error:" + string(SDL_GetError())),LOG_ERROR);
}

void JoystickControl::JoyPressed(){
	//X axis motion
	if( evento->jaxis.axis == 0 ){
		//Left of dead zone
		if( evento->jaxis.value < -JOYSTICK_DEAD_ZONE ){
			personaje->CaminarIzquierda();
		}
		//Right of dead zone
		else if( evento->jaxis.value > JOYSTICK_DEAD_ZONE ){
			personaje->CaminarDerecha();
		}
		else{
			//NO SE
		}
	}
	//Y axis motion
	else if( evento->jaxis.axis == 1 ){
		//arriba
		if( evento->jaxis.value < -JOYSTICK_DEAD_ZONE ){
			personaje->Saltar();
		}
		//abajo
		else if( evento->jaxis.value > JOYSTICK_DEAD_ZONE){
			personaje->Agachar();
		}
		else{
			//NADA
		}
	}
}

void JoystickControl::JoyState(){
	Sint16 x_mov = SDL_JoystickGetAxis(joystick,0);
	Sint16 y_mov = SDL_JoystickGetAxis(joystick,1);
	int sentido_personaje = personaje->getSentidoDeMovimiento();

	//frena si no se esta manteniendo para un lado el analogico
	if ( ( sentido_personaje > 0 && x_mov < JOYSTICK_DEAD_ZONE ) || (sentido_personaje < 0 && x_mov > -JOYSTICK_DEAD_ZONE)  )
		personaje->Frenar();

	//se levanta si no esta manteniendo para abajo el analogico
	if (y_mov > -JOYSTICK_DEAD_ZONE)
		personaje->Levantarse();
}

JoystickControl::~JoystickControl() {
	personaje = NULL;
	if (joystick != NULL ){
		SDL_JoystickClose( joystick );
		joystick = NULL;
	}
}

