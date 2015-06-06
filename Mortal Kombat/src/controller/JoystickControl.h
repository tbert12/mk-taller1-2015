/*
 * JoystickControl.h
 *
 *  Created on: 28/4/2015
 *      Author: facu
 */

#ifndef SRC_CONTROLLER_JOYSTICKCONTROL_H_
#define SRC_CONTROLLER_JOYSTICKCONTROL_H_

//maximo en el analogico
#define JOYSTICK_MAX_ZONE 32767
#define JOYSTICK_DEAD_ZONE 32000

//botones joy
#define JOY_TRIANGULO 0
#define JOY_CIRCULO 1
#define JOY_X 2
#define JOY_CUADRADO 3
#define JOY_L1 4
#define JOY_L2 5
#define JOY_R1 6
#define JOY_R2 7
#define JOY_SELECT 8
#define JOY_START 9
#define JOY_L3 10
#define JOY_R3 11

//mapa de comandos
#define PINA_BAJA string("pina baja")
#define PATADA_BAJA string("patada baja")
#define PINA_ALTA string("pina alta")
#define PATADA_ALTA string("patada alta")
#define	CUBRIRSE string("cubrirse")
#define LANZAR_ARMA string("lanzar arma")

#define BUTTON_PRESSED 1
#define BUTTON_UNPRESSED 0


#include "../model/logging.h"
#include "../model/Personaje.h"
#include "ComboController.h"
#include <SDL2/SDL.h>
#include <string>
#include <map>

class JoystickControl {
public:
	JoystickControl(SDL_Event* e,int id_joystick,Personaje* un_personaje,map<string, int>* mapa_comandos,ComboController* comboCon);
	void JoyPressed();
	void JoyState();
	bool pause();
	virtual ~JoystickControl();

private:
	SDL_Event* evento;
	SDL_Joystick* joystick;
	SDL_Haptic* joystickHaptic;
	Personaje* personaje;
	map<string, int>* comandos;
	bool pausa;
	ComboController* comboController;

	void _Init(int id);
	void _verificarMapaComandos();
};

#endif /* SRC_CONTROLLER_JOYSTICKCONTROL_H_ */
