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
#include "../model/Pelea.h"


class Controller {
private:
	Personaje* personaje_1;
	Personaje* personaje_2;
	Pelea* pelea;
	KeyboardControl* Teclado;
	JoystickControl* Joystick_1;
	JoystickControl* Joystick_2;
	bool quit;
	int ModoDeJuego;
	const Uint8* keystate;
	SDL_Event evento;
	ComboController* _comboController;

	void _Init(map<string, int>* mapa_comandos1,map<string, int>* mapa_comandos2,int tiempoMax, int tolerancia);
	void _JoystickRemoved();
	void _JoystickAdded();

public:
	Controller(Pelea* una_pelea,map<string, int>* mapa_comandos1,map<string, int>* mapa_comandos2,int tiempoMax, int tolerancia);
	bool Quit();
	bool PollEvent();
	void Pressed();
	void KeyState();
	bool pausa();
	int getSleep();
	bool checkCombos();
	virtual ~Controller();
};

#endif /* SRC_CONTROLLER_CONTROLLER_H_ */
