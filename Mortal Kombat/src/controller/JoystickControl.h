/*
 * JoystickControl.h
 *
 *  Created on: 28/4/2015
 *      Author: facu
 */

#ifndef SRC_CONTROLLER_JOYSTICKCONTROL_H_
#define SRC_CONTROLLER_JOYSTICKCONTROL_H_

//maximo en el analogico
#define JOYSTICK_DEAD_ZONE 8000

#include "../model/logging.h"
#include "../model/Personaje.h"
#include <SDL2/SDL.h>

//CUANTOS JOYSTICK, para el parser seguro!
int cantidad_de_Joystick(){
	return SDL_NumJoysticks();
}

class JoystickControl {
public:
	JoystickControl(SDL_Event e,Personaje* un_personaje);
	bool PollEvent();
	void JoyPressed();
	virtual ~JoystickControl();

private:
	SDL_Event evento;
	SDL_Joystick* joystick;
	Personaje* personaje;

	void _Init();
};

#endif /* SRC_CONTROLLER_JOYSTICKCONTROL_H_ */
