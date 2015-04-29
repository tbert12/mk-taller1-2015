/*
 * JoystickControl.h
 *
 *  Created on: 28/4/2015
 *      Author: facu
 */

#ifndef SRC_CONTROLLER_JOYSTICKCONTROL_H_
#define SRC_CONTROLLER_JOYSTICKCONTROL_H_

#include "../model/logging.h"
#include <SDL2/SDL.h>


class JoystickControl {
public:
	JoystickControl();
	virtual ~JoystickControl();

private:
	SDL_Joystick* joystick;
	int cant_joystick;
};

#endif /* SRC_CONTROLLER_JOYSTICKCONTROL_H_ */
