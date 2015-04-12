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

	reverse = false;

	//Se queda Loopeando en 1 Frame
	doloop = false;
	frameLoop = 0;

	if( !SpriteSheetTexture->loadFromFile( ruta ) ){
		log( "Error al intentar abrir la imagen del sprite.", LOG_ERROR );
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

float Sprite::getAncho(){
	return spriteFrames[frameActual].w;
}

bool Sprite::Advance(){
	if (!doloop){
		if (reverse)
			frameActual--;
		else
			frameActual++;
	} else {
		if (frameActual != frameLoop){
			if (reverse)
				frameActual--;
			else
				frameActual++;
		}
	}
	if (frameActual >= cantidadFrames or frameActual < 0){
		Reset();
	}
	printf("FrameActual: %d | Cantidad: %d\n",frameActual,cantidadFrames);
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
	if (reverse) frameActual = cantidadFrames - 1;
	else frameActual = 0;
}

void Sprite::render(float x, float y, bool fliped){
	Rect_Logico* currentClip = &spriteFrames[frameActual];
	SpriteSheetTexture->renderObjeto(currentClip,x ,y - currentClip->h, fliped);
}

void Sprite::setLoop(int num_frame) {
	if (num_frame >= cantidadFrames ) return;
	frameLoop = num_frame;
}

void Sprite::doLoop(bool loop){
	doloop = loop;
}

void Sprite::Reverse(bool Reverse){
	reverse = Reverse;
}

bool Sprite::ultimoFrame(){
	return (frameActual + 1 == cantidadFrames and !doloop);
}
