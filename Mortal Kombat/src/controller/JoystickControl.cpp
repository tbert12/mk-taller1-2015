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
	pausa = false;
	_Init(id_joystick);
}

bool JoystickControl::pause(){
	return pausa;
}

void JoystickControl::_Init(int id){
	joystick =	NULL;
	joystickHaptic = NULL;
	if(SDL_NumJoysticks() < id +1) log("No se puede abrir el joystick",LOG_ERROR);
	else joystick = SDL_JoystickOpen( id );
	if( joystick == NULL ) log(string("No se puede leer el joystick! SDL Error:" + string(SDL_GetError())),LOG_ERROR);
	else{
		log("Joystick cargado correctamente",LOG_DEBUG);
		//joystickHaptic = SDL_HapticOpenFromJoystick( joystick );
		if( joystickHaptic == NULL ){
			log(string("El Joystick no soporta haptics! SDL Error:" + string(SDL_GetError())),LOG_WARNING);
		}
		else{
			//Get initialize rumble
			if( SDL_HapticRumbleInit( joystickHaptic ) < 0 ){
				log(string("Unable to initialize rumble! SDL Error:" + string(SDL_GetError())),LOG_WARNING);
			}
		}
	}
}

void JoystickControl::JoyPressed(){
	//X axis motion
	if(evento->type == SDL_JOYAXISMOTION){
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
	//Boton
	else if (evento->type == SDL_JOYBUTTONUP){
		switch(evento->jbutton.button){
			case JOY_X:
				personaje->pinaBaja();
				break;
			case JOY_CUADRADO:
				personaje->pinaAlta();
				if (SDL_JoystickGetAxis(joystick,1) > JOYSTICK_DEAD_ZONE )
					if (joystickHaptic != NULL)
						SDL_HapticRumblePlay( joystickHaptic, 0.75, 700 );
				break;
			case JOY_CIRCULO:
				personaje->patadaBaja();
				break;
			case JOY_TRIANGULO:
				personaje->patadaAlta();
				break;
			case JOY_R1:
				personaje->cubrirse();
				break;
			case JOY_START:
				pausa = !pausa;
				break;
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
	if (!(y_mov > JOYSTICK_DEAD_ZONE))
		personaje->Levantarse();

	//se deja de cubrir si no esta apretado
	//if (SDL_JoystickGetButton(joystick,JOY_R1) == BUTTON_UNPRESSED);
		//personaje->dejarDeCubrirse();

}

JoystickControl::~JoystickControl() {
	personaje = NULL;
	if (joystick != NULL && SDL_JoystickGetAttached(joystick)){
		SDL_JoystickClose( joystick );
		joystick = NULL;
	}
	if (joystickHaptic != NULL){
		SDL_HapticClose(joystickHaptic);
		joystickHaptic = NULL;
	}
}

