/*
 * Personaje.cpp
 *
 *  Created on: 26/3/2015
 *      Author: facu
 */

#include "Personaje.h"

Personaje::Personaje(std::string nombre_personaje,std::vector<Sprite*> Sprites, float velocidad) {
	nombre = nombre_personaje;
	vida = 100;
	sprites = Sprites;
	spriteActual = sprites[SPRITE_INICIAL];
	m_xActual = 0;
	m_yActual = 0;
	m_velocidad = velocidad;
	estaScrolleando = false;
}

std::vector<Sprite*> Personaje::getSprites(){
	return sprites;
}

Sprite* Personaje::getSpriteActual(){
	return spriteActual;
}

int Personaje::Vida(){
	return vida;
}

void Personaje::SetScroll(bool valor){
	estaScrolleando = valor;
}

void Personaje::_cambiarSprite(int accion){
	//Con la logica del salto tengo que mantener Reseteando el SPRITE_SALTO asi no se pasa
	if (sprites[accion] != spriteActual){
		spriteActual = sprites[accion];
		spriteActual->Reset();
	} else if (!spriteActual->puedeAvanzar()){
		spriteActual = spriteActual->getSpriteSiguiente();
		spriteActual->Reset();
	}
}

void Personaje::Inicial(){
	if (spriteActual == sprites[SPRITE_SALTO]){
		//Capas que tenga que hacer un booleano para saber si esta saltando
		this->_cambiarSprite(SPRITE_SALTO_CAIDA);
	} else {
		this->_cambiarSprite(SPRITE_INICIAL);
	}
}

void Personaje::CaminarDerecha(){
	this->_cambiarSprite(SPRITE_CAMINAR_DERECHA);
	if (estaScrolleando) {
		estaScrolleando = false;
		return;
	}
	m_xActual += m_velocidad;
}

void Personaje::CaminarIzquierda(){
	this->_cambiarSprite(SPRITE_CAMINAR_IZQUIERDA);
	if (estaScrolleando) {
		return;
	}
	m_xActual -= m_velocidad;
}

void Personaje::Saltar(){
	this->_cambiarSprite(SPRITE_SALTO_ANTES);
	//Saltar
}

void Personaje::SaltarDerecha(){
	this->_cambiarSprite(SPRITE_SALTO_DIAGONAL_DERECHA);
	//aca saltar
	if (estaScrolleando) {
		return;
	}
}

void Personaje::SaltarIzquierda(){
	this->_cambiarSprite(SPRITE_SALTO_DIAGONAL_IZQUIERDA);
	//aca saltar
	if (estaScrolleando) {
		return;
	}
}


void Personaje::Agachar(){}

int Personaje::getX()
{
	return m_xActual;
}

int Personaje::getY()
{
	return m_yActual;
}

void Personaje::QuitarVida(int valor){
	vida = vida - valor;
	if(vida < 0){
		vida = 0;
	}
}

Personaje::~Personaje() {
	//~sprites();
	//~nombre();
	//sprites.~list();
	//nombre.~string();
}

