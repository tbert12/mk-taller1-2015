/*
 * KeyboardControl.h
 *
 *  Created on: 26/3/2015
 *      Author: tomi
 */

#ifndef SRC_CONTROLLER_KEYBOARDCONTROL_H_
#define SRC_CONTROLLER_KEYBOARDCONTROL_H_

#include<SDL2/SDL.h>
#include "../model/Personaje.h"

class KeyboardControl {
	Personaje* personaje;
	bool quit;
	bool agachado;
public:
	KeyboardControl(Personaje*);
	virtual ~KeyboardControl();
	void KeyPressed(SDL_Event evento);
	bool getQuit();
};

#endif /* SRC_CONTROLLER_KEYBOARDCONTROL_H_ */
