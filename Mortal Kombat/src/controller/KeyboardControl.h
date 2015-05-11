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
#include <exception>
#include <map>

using namespace std;

class KeyboardControl {
private:
	Personaje* personaje;
	const Uint8* keystate;
	SDL_Event* evento;
	bool pausa;
	bool como_jugador;
	int sleep;

public:
	KeyboardControl(SDL_Event* e, Personaje* un_personaje,bool como_jugador);
	virtual ~KeyboardControl();
	void KeyPressed();
	void KeyState();
	int getSleep();
	bool pause();
};

#endif /* SRC_CONTROLLER_KEYBOARDCONTROL_H_ */
