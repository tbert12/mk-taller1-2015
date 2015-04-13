/*
 * Sprite.cpp
 *
 *  Created on: 31/3/2015
 *      Author: tomi
 */

#include "Sprite.h"

Sprite::Sprite(std::string ruta,std::vector<Frame*> frames,Ventana* ventana){
	frameActual = 0;
	SpriteSheetTexture = ventana->crearTextura();

	reverse = false;

	//Loopear en 1 Frame
	doloop = false;
	frameLoop = 0;

	if( !SpriteSheetTexture->loadFromFile( ruta ) ){
		log( "Error al intentar abrir la imagen del sprite.", LOG_ERROR );
		throw CargarImagenException( "No se pudo cargar la imagen del sprite como textura SDL" );
	}

	cantidadFrames = frames.size();
	
	spriteFrames = new Rect_Logico[cantidadFrames];
	for (int i=0;i < cantidadFrames;i++){
		spriteFrames[i].x = frames[i]->X;
		spriteFrames[i].y = frames[i]->Y;
		spriteFrames[i].h = frames[i]->Alto;
		spriteFrames[i].w = frames[i]->Ancho;
		delete frames[i];
	}
}

Sprite::~Sprite(){
	SpriteSheetTexture->free();
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
	return true;
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

void Sprite::doReverse(bool Reverse){
	reverse = Reverse;
}

bool Sprite::ultimoFrame(){
	if (doloop) return false;
	if (reverse){
		return (frameActual == 0);
	}
	return (frameActual + 1 == cantidadFrames);
}
