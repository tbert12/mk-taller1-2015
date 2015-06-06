/*
 * ControlModo.h
 *
 *  Created on: 30/5/2015
 *      Author: facu
 */

#ifndef SRC_CONTROLLER_CONTROLMODO_H_
#define SRC_CONTROLLER_CONTROLMODO_H_

#include <SDL2/SDL.h>
#include "../model/MenuSeleccion.h"

#define JOYSTICK_DEAD_ZONE 32000

class ControlModo {
private:
	MenuSeleccion* menu;
	const Uint8* keystate;
	SDL_Event evento;
	bool quit;
	SDL_Joystick* joystick;

public:
	ControlModo(MenuSeleccion* un_menu);
	void Pressed();
	void KeyState();
	bool PollEvent();
	int getModoDeJuego();
	bool Quit();
	virtual ~ControlModo();
};

#endif /* SRC_CONTROLLER_CONTROLMODO_H_ */
