/*
 * Sprite.cpp
 *
 *  Created on: 31/3/2015
 *      Author: tomi
 */

#include "Sprite.h"

Sprite::Sprite(std::string ruta,std::vector<Frame*> frames,Ventana* ventana){
	frameActual = 0;
	spriteSiguiente = NULL;
	SpriteSheetTexture = ventana->crearTextura();

	if( !SpriteSheetTexture->loadFromFile( ruta ) ){
		printf( "Error en cargar Sprite\n" );
		//Usemos la funcion log( mensaje ) en logging.h para este tipo de cosas.
	}
	cantidadFrames = frames.size();
	
	spriteFrames = new Rect_Logico[cantidadFrames];
	for (int i=0;i < cantidadFrames;i++){
		spriteFrames[i].x = frames[i]->X;
		spriteFrames[i].y = frames[i]->Y;
		spriteFrames[i].h = frames[i]->Alto;
		spriteFrames[i].w = frames[i]->Ancho;
		//frames[i]->~Frame();
	}
}

Sprite::~Sprite(){
	SpriteSheetTexture->free();
}

Rect_Logico* Sprite::getFrame() {
	Rect_Logico* frame = &spriteFrames[frameActual];
	return frame;
}

bool Sprite::Advance(){
	//Es necesario el bool?
	frameActual++;
	if (frameActual >= cantidadFrames){
		frameActual = 0;
	}
<<<<<<< HEAD
<<<<<<< HEAD
	//printf("Frame: %d | TotalFrame: %d\n",frameActual,cantidadFrames);
=======
>>>>>>> 85bd7a198744ff541d20009763ef9ffefbdd3060
=======
	//printf("Frame: %d | TotalFrame: %d\n",frameActual,cantidadFrames);
>>>>>>> 681dc3d792734f4f43374f18646978992de41ee4
	return true;
}

Sprite* Sprite::getSpriteSiguiente(){
	return spriteSiguiente;
}

bool Sprite::puedeAvanzar(){
	if (frameActual + 1 >= cantidadFrames){
		if (spriteSiguiente){
			return false;
		}
	}
	return true;
}

LTexture* Sprite::getSpriteSheetTexture(){
	return SpriteSheetTexture;
}

void Sprite::setSpriteSiguiente(Sprite* nextsprite){
	spriteSiguiente = nextsprite;
}

void Sprite::Reset(){
	frameActual = 0;
}

void Sprite::render(float x, float y){
	Rect_Logico* currentClip = &spriteFrames[frameActual];
	SpriteSheetTexture->renderObjeto(currentClip,x ,y - currentClip->h);
}

