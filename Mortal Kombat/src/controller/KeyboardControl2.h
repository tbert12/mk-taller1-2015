/*
 * KeyboardControl2.h
 *
 *  Created on: 26/3/2015
 *      Author: tomi
 */

#ifndef SRC_CONTROLLER_KEYBOARDCONTROL2_H_
#define SRC_CONTROLLER_KEYBOARDCONTROL2_H_

#include<SDL2/SDL.h>
#include "../model/Personaje.h"
#include <exception>

class KeyboardControl2 {
private:
	Personaje* personaje;
	bool quit;
	bool agachado;
	const Uint8* keystate;
	SDL_Event evento;

public:

	KeyboardControl2(Personaje*);
	virtual ~KeyboardControl2();

	bool PollEvent();

	void KeyPressed();
	void KeyState();
	bool getQuit();
	bool recargar();
};

#endif /* SRC_CONTROLLER_KEYBOARDCONTROL2_H_ */
