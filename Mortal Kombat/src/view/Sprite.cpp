/*
 * Sprite.cpp
 *
 *  Created on: 31/3/2015
 *      Author: tomi
 */

#include "Sprite.h"

Sprite::Sprite(std::string ruta,std::vector<Frame*> frames){
	// NO SE LE PUEDE SACAR EL VECTOR DE FRAMES Y EL SDL_RENDERER AL CONSTRUCTOR?
	// SINO SE COMPLICA MUCHISIMO PARA LLAMARLO DESDE EL PARSER.
	frameActual = 0;
	spriteSiguiente = NULL;
	SpriteSheetTexture = new LTexture(Renderer);

	if( !SpriteSheetTexture->loadFromFile( ruta ) ){
		printf( "Error en cargar Sprite\n" );
		//Usemos la funcion log( mensaje ) en logging.h para este tipo de cosas.
	}
	cantidadFrames = frames.size();
	
	spriteFrames = new SDL_Rect[cantidadFrames];
	for (int i=0;i < cantidadFrames;i++){
		spriteFrames[i].x = frames[i]->X;
		spriteFrames[i].y = frames[i]->Y;
		spriteFrames[i].h = frames[i]->Alto;
		spriteFrames[i].w = frames[i]->Ancho;
	}
}

Sprite::~Sprite(){
	//Los Frames se deben liberar apenas se carga
	//Elimino Sprite
	//SpriteSheetTexture.free();
}

void Sprite::setRender(SDL_Renderer* Renderer){
}

SDL_Rect* Sprite::getFrame(){
	SDL_Rect* frame = &spriteFrames[frameActual];
	printf("Frame: %d | Cant: %d\n",frameActual,cantidadFrames);

	return frame;
}

bool Sprite::Advance(){
	//Es necesario el bool?
	frameActual++;
	if (frameActual >= cantidadFrames){
		frameActual = 0;
	}
	return true;
}

Sprite* Sprite::getSpriteSiguiente(){
	return spriteSiguiente;
}

bool Sprite::puedeAvanzar(){
	if (frameActual >= cantidadFrames){
		if (spriteSiguiente){
			return false;
		}
	}
	return true;
}

LTexture* Sprite::getSpriteSheetTexture(){
	return SpriteSheetTexture;
}

void Renderizar(){

}

void Sprite::Reset(){
	frameActual = 0;
}


