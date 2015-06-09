/*
 * SoundMenu.h
 *
 *  Created on: 9/6/2015
 *      Author: facu
 */

#ifndef SRC_VIEW_SOUNDMENU_H_
#define SRC_VIEW_SOUNDMENU_H_

#include "../view/LSound.h"
#define RUTA_SOUND_FONDO "data/sound/menu/fondo.wav"
#define RUTA_SOUND_SELECT "data/sound/menu/select.wav"
#define RUTA_SOUND_MOVE "data/sound/menu/move.wav"

enum SOUNDS {FONDO , SELECT , MOVE};

class SoundMenu {
public:
	SoundMenu();
	void play(int sound);
	void stop(int sound);
	virtual ~SoundMenu();
private:
	LSound* fondo;
	LSound* select;
	LSound* move;
};

#endif /* SRC_VIEW_SOUNDMENU_H_ */
