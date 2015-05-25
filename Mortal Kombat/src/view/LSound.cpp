/*
 * LSound.cpp
 *
 *  Created on: 23/5/2015
 *      Author: tomi
 */

#include "LSound.h"

LSound::LSound(std::string rutaSonido) {
	/* Carga clip en WAV */
	mSound = Mix_LoadWAV( rutaSonido.c_str() );
	if (mSound == NULL){
		log( std::string("Imposible cargar Sonido: %s", Mix_GetError() ),LOG_WARNING);
	} else {
		log( std::string("Sonido cargado correctamente: ") + rutaSonido ,LOG_DEBUG);
	}

}

void LSound::play(){
	/* Mix_PlayChannel(int channel,Mix_Chunk* sound,int loop)
	 *  -channel: Elegir canal para reproducirlo.
	 *  		  con -1 lo reproduce en el primero que esta libre.
	 *  -loop: loopear el sonido n veces (-1 eq infinito)
	 *  -sound: =?
	 */
	Mix_PlayChannel( -1, mSound, 0 );
}

LSound::~LSound() {
	Mix_FreeChunk(mSound);
}

