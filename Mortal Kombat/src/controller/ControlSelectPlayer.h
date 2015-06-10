/*
 * ControlSelectPlayer.h
 *
 *  Created on: 5/6/2015
 *      Author: facu
 */

#ifndef SRC_CONTROLLER_CONTROLSELECTPLAYER_H_
#define SRC_CONTROLLER_CONTROLSELECTPLAYER_H_

#include "../model/SelectPlayer.h"
#include "../view/TextBox.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_joystick.h>

#define JOYSTICK_DEAD_ZONE 32000

class ControlSelectPlayer {
private:
	SelectPlayer* menuPlayers;
	const Uint8* keystate;
	SDL_Event evento;
	SDL_Joystick* joystick1;
	SDL_Joystick* joystick2;
	bool quit;
	bool textBoxOpen;
	void _textBoxPressed();
	void openTextBox();
	void closeTextBox();
public:
	ControlSelectPlayer(SelectPlayer* select,bool dos_jugadores);
	void Pressed();
	void KeyState();
	bool PollEvent();
	int getModoDeJuego();
	bool Quit();
	virtual ~ControlSelectPlayer();

};

#endif /* SRC_CONTROLLER_CONTROLSELECTPLAYER_H_ */
