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
		log( std::string("Imposible cargar Sonido: ") + Mix_GetError() ,LOG_WARNING);
	} else {
		log( std::string("Sonido cargado correctamente: ") + rutaSonido ,LOG_DEBUG);
	}

}

void LSound::play(int loop){
	/* Mix_PlayChannel(int channel,Mix_Chunk* sound,int loop)
	 *  -channel: Elegir canal para reproducirlo.
	 *  		  con -1 lo reproduce en el primero que esta libre.
	 *  -loop: loopear el sonido n veces (-1 eq infinito)
	 *  -sound: =?
	 */
	if (mSound == NULL) return;
	Mix_PlayChannel( -1, mSound, loop );
}

void LSound::stop(){
	if (mSound == NULL) return;
	Mix_HaltChannel(-1); // ahi paro todos :( hay que parar por canal
}

LSound::~LSound() {
	if (mSound != NULL) {
		Mix_FreeChunk(mSound);
	}
}

