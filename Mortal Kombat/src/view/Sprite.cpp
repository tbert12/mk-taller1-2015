/*
 * Sprite.cpp
 *
 *  Created on: 31/3/2015
 *      Author: tomi
 */

#include "Sprite.h"

Sprite::Sprite(std::string ruta,std::vector<Frame*> frames,Ventana* ventana,float ratio_x, float ratio_y){
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
	
	spriteFrames = new Rect_Objeto[cantidadFrames];
	for (int i=0;i < cantidadFrames;i++){
		spriteFrames[i].x = frames[i]->X;
		spriteFrames[i].y = frames[i]->Y;
		spriteFrames[i].h = frames[i]->Alto;
		spriteFrames[i].w = frames[i]->Ancho;
		spriteFrames[i].w_log = frames[i]->Ancho/ratio_x;
		spriteFrames[i].h_log = frames[i]->Alto/ratio_y;

		delete frames[i];
	}
}

Sprite::~Sprite(){
	delete SpriteSheetTexture;
	delete []spriteFrames;
}

float Sprite::getAncho(){
	return spriteFrames[frameActual].w_log;
}

float Sprite::getAlto(){
	return spriteFrames[frameActual].h_log;
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
	Rect_Objeto* currentClip = &spriteFrames[frameActual];
	float correrX;
	if (fliped) correrX = currentClip->w_log;
	else correrX = 0;
	SpriteSheetTexture->renderObjeto(currentClip,x - correrX ,y - currentClip->h_log, fliped);
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
