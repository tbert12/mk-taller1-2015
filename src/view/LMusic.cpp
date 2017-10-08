/*
 * LMusic.cpp
 *
 *  Created on: 9/6/2015
 *      Author: tomi
 */

#include "LMusic.h"

/* A esta clase se le puede agregar
 * 	-Control de Volumen
 * 	-Que el sonido haga efectos de FadeIn y FadeOut
 */


namespace std {

LMusic::LMusic(string ruta,int un_chanel) {
	reproduciendose = false;
	pausada = false;
	channel = un_chanel;
	gMusic = Mix_LoadMUS( ruta.c_str() );
	if( gMusic == NULL ) {
		//log( "Fallo al cargar Musica (" + ruta + ")! SDL_mixer Error: " /*+ string( Mix_GetError()*/, LOG_WARNING );
	}

}

void LMusic::play(int loops){
	//Si cuando la repoducir le mandas un channel tenes que controlarla por ese channel
	//Si le das Play sin atributos controlas el stream por completo
	if( gMusic == NULL ) return;
	if (reproduciendose) return;
	//Referido al Stream en completo
	if( !Mix_Playing(channel) ){
		Mix_PlayMusic( gMusic, loops );
	}
	reproduciendose = true;

}

void LMusic::pause(){
	if( gMusic == NULL ) return;
	if (pausada) return;
	if (channel != -1)
		Mix_Pause(channel);
	else
		Mix_PauseMusic();
	pausada = true;
}

void LMusic::stop(){
	if( gMusic == NULL ) return;
	if (channel != -1)
		Mix_HaltMusic();
	else
		Mix_HaltChannel(channel);
	reproduciendose = false;
	pausada = false;
}

bool LMusic::estaReproduciendose(){
	return (reproduciendose and !pausada);
}

bool LMusic::estaPausada(){
	return pausada;
}

int LMusic::getChannel(){
	return channel;
}

LMusic::~LMusic() {
	if( gMusic != NULL )Mix_FreeMusic( gMusic );
	gMusic = NULL;
}

} /* namespace std */
