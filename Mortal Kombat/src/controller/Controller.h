/*
 * Controller.h
 *
 *  Created on: 29/4/2015
 *      Author: facu
 */

#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "JoystickControl.h"
#include "KeyboardControl.h"
#include "../model/Personaje.h"


class Controller {
private:
	Personaje* personaje_1;
	Personaje* personaje_2;
	KeyboardControl* Teclado;
	JoystickControl* Joystick_1;
	JoystickControl* Joystick_2;
	bool quit;
	const Uint8* keystate;
	SDL_Event evento;

	void _Init();
	void _JoystickRemoved();

public:
	Controller(Personaje* un_personaje,Personaje* otro_personaje);
	bool Quit();
	bool PollEvent();
	void Pressed();
	void KeyState();

	virtual ~Controller();
};

#endif /* SRC_CONTROLLER_CONTROLLER_H_ */
