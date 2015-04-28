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
	bool quit;
	bool agachado;
	const Uint8* keystate;
	map<const char*, char> mapa_comandos;
	SDL_Event evento;

public:
	KeyboardControl(SDL_Event, map <const char*, char> , Personaje*);
	virtual ~KeyboardControl();

	bool PollEvent();

	void KeyPressed();
	void KeyState();
	bool getQuit();
	bool recargar();
};

#endif /* SRC_CONTROLLER_KEYBOARDCONTROL_H_ */
