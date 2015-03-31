/*
 * Sprite.cpp
 *
 *  Created on: 31/3/2015
 *      Author: tomi
 */

#include <string>
#include "Sprite.h"

bool Sprite::Sprite(std::string ruta, Frame frames[]){

	frameActual = 0;
	if( !SpriteSheetTexture.loadFromFile( ruta ) )
		{
			printf( "Error en cargar Sprite\n" );
			return false;
		}
	int cantidadFrames = sizeof(frames)/sizeof(*frames);
	for (int i=0;i < cantidadFrames;i++){
		spriteFrames[i].x = frames[i].X;
		spriteFrames[i].y = frames[i].Y;
		spriteFrames[i].h = frames[i].Alto;
		spriteFrames[i].w = frames[i].Ancho;
		~frames[i]();
	}
	return true;
}

Sprite::~Sprite(){
	//Los Frames se deben liberar apenas se carga
	//Elimino Sprite
	SpriteSheetTexture.free();
}

SDL_Rect Sprite::nextFrame(){
	SDL_Rect frame = spriteFrames[frameActual];
	frameActual++;
	if (frameActual >= cantidadFrames){
		frameActual = 0;
	}
	return frame;
}


