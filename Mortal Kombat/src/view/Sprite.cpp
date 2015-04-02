/*
 * Sprite.cpp
 *
 *  Created on: 31/3/2015
 *      Author: tomi
 */

#include "Sprite.h"

Sprite::Sprite(std::string ruta,std::vector<Frame*> frames,SDL_Renderer* Renderer){
	// NO SE LE PUEDE SACAR EL VECTOR DE FRAMES Y EL SDL_RENDERER AL CONSTRUCTOR?
	// SINO SE COMPLICA MUCHISIMO PARA LLAMARLO DESDE EL PARSER.
	frameActual = 0;
	SpriteSheetTexture = new LTexture(Renderer);
	if( !SpriteSheetTexture->loadFromFile( ruta ) )
		{
			printf( "Error en cargar Sprite\n" );
			 // Usemos la funcion log( mensaje ) en logging.h para este tipo de cosas.
			// Registra en el archivo .log los errores de acuerdo al nivel.
		}
	
	cantidadFrames = frames.size();
	//Como sorete obtengo la cantidad de frames <--- JAJAJA
	
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

SDL_Rect* Sprite::getFrame(){
	SDL_Rect* frame = &spriteFrames[frameActual];
	printf("Frame: %d | Cant: %d\n",frameActual,cantidadFrames);

	return frame;
}

bool Sprite::Advance(){
	frameActual++;
	if (frameActual >= cantidadFrames){
		frameActual = 0;
	}
	return true;
}

LTexture* Sprite::getSpriteSheetTexture(){
	return SpriteSheetTexture;
}

void Sprite::Reset(){
	frameActual = 0;
}


