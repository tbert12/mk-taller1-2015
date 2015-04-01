/*
 * Sprite.cpp
 *
 *  Created on: 31/3/2015
 *      Author: tomi
 */

#include "Sprite.h"

Sprite::Sprite(std::string ruta,std::vector<Frame*> frames,SDL_Renderer* Renderer){
	frameActual = 0;
	SpriteSheetTexture = new LTexture(Renderer);
	if( !SpriteSheetTexture->loadFromFile( ruta ) )
		{
			printf( "Error en cargar Sprite\n" );
		}
	
	cantidadFrames = frames.size();
	//Como sorete obtengo la cantidad de frames
	
	spriteFrames = new SDL_Rect[cantidadFrames];
	for (int i=0;i < cantidadFrames;i++){
		spriteFrames[i].x = frames[i]->X;
		spriteFrames[i].y = frames[i]->Y;
		spriteFrames[i].h = frames[i]->Alto;
		spriteFrames[i].w = frames[i]->Ancho;
		//~frames[i](); Nose como si lebera el frames[i], ya no es mas ultil
	}
}

Sprite::~Sprite(){
	//Los Frames se deben liberar apenas se carga
	//Elimino Sprite
	//SpriteSheetTexture.free();
}

SDL_Rect* Sprite::nextFrame(){
	SDL_Rect* frame = &spriteFrames[frameActual];
	printf("Frame: %d | Cant: %d\n",frameActual,cantidadFrames);
	frameActual++;
	if (frameActual >= cantidadFrames){
		frameActual = 0;
	}
	return frame;
}

LTexture* Sprite::getSpriteSheetTexture(){
	return SpriteSheetTexture;
}

void Sprite::Reset(){
	frameActual = 0;
}


