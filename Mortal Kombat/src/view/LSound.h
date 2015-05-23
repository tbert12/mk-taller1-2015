/*
 * LSound.h
 *
 *  Created on: 23/5/2015
 *      Author: tomi
 */
#ifndef SRC_VIEW_LSOUND_H_
#define SRC_VIEW_LSOUND_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <stdio.h>
#include "../model/logging.h"

class LSound {
	private:
		Mix_Chunk* mSound;

	public:
		LSound(std::string ruta);
		void play();
		virtual ~LSound();
};

#endif /* SRC_VIEW_LSOUND_H_ */
