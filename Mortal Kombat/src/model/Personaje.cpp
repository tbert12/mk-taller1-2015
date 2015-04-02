/*
 * Personaje.cpp
 *
 *  Created on: 26/3/2015
 *      Author: facu
 */

#include "Personaje.h"

Personaje::Personaje(std::string nombre_personaje,std::vector<Sprite*> Sprites, float velocidad) {
	spriteActual = 0;
	nombre = nombre_personaje;
	vida = 100;
	sprites = Sprites;
	m_xActual = 0;
	m_yActual = 0;
	m_velocidad = velocidad;
	estaScrolleando = false;

	//COMO ES UN SOLO JUGADOR EN ESTE TP LO HARCODEAMOS, LUEGO LO LEVANTAMOS CON JSON
	//sprites = std::list<std::string> sprites("data/players/subzero/sprites/initial.png");
	//sprites = "data/players/subzero/sprites/walk.png";
}

std::vector<Sprite*> Personaje::getSprites(){
	return sprites;
}

Sprite* Personaje::getSpriteActual(){
	return sprites[spriteActual];
}

int Personaje::Vida(){
	return vida;
}

void Personaje::_cambiarSprite(Accion* accion){
	if (accion != spriteActual){
		if(accion->getSiguiente() != 0){
			spriteActual = accion->getSiguiente();
			return;
		}
		spriteActual = accion->getAccion();
		sprites[spriteActual]->Reset();
	}
}

void Personaje::Inicial(){
	this->_cambiarSprite(0);
}

void Personaje::Saltar(){
}


void Personaje::Agachar(){}

void Personaje::CaminarDerecha(){
	this->_cambiarSprite(SPRITE_CAMINAR);
	if (estaScrolleando) {
		return;
	}
	m_xActual += m_velocidad;
}

void Personaje::CaminarIzquierda(){
	this->_cambiarSprite(SPRITE_CAMINAR_ATRAS);
	if (estaScrolleando) {
		return;
	}
	m_xActual -= m_velocidad;
}

void Personaje::SaltarDerecha(){}

void Personaje::SaltarIzquierda(){}

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

