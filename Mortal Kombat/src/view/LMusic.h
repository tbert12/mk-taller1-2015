/*
 * LMusic.h
 *
 *  Created on: 9/6/2015
 *      Author: tomi
 */

#ifndef SRC_VIEW_LMUSIC_H_
#define SRC_VIEW_LMUSIC_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include "../model/logging.h"

namespace std {

class LMusic {
private:
	Mix_Music *gMusic;
	bool reproduciendose;
	bool pausada;

	int channel;

public:
	LMusic(string ruta);
	virtual ~LMusic();

	void play(int channel);
	void pause();
	void stop();

	int getChannel();

	bool estaReproduciendose();
	bool estaPausada();
};

} /* namespace std */

#endif /* SRC_VIEW_LMUSIC_H_ */
