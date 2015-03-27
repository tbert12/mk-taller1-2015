/*
 * KeyboardControl.h
 *
 *  Created on: 26/3/2015
 *      Author: facu
 */

#ifndef SRC_CONTROLLER_KEYBOARDCONTROL_H_
#define SRC_CONTROLLER_KEYBOARDCONTROL_H_

#include<SDL2/SDL.h>
#include "../model/Personaje.h"

class KeyboardControl {
	Personaje* personaje;
public:
	KeyboardControl(Personaje* un_personaje);
	virtual ~KeyboardControl();
	void KeyPressed(SDL_Event evento);
};

#endif /* SRC_CONTROLLER_KEYBOARDCONTROL_H_ */
